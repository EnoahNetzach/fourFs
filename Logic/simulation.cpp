/*
 * simulation.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: Enoah Netzach
 */

#include "simulation.h"

#include <boost/chrono.hpp>
#include <boost/foreach.hpp>
#ifdef DEBUG
#include <lua/lua.hpp>
#endif // DEBUG
#include <boost/random.hpp>
#include <boost/scope_exit.hpp>

#include "../logger.h"
#ifndef DEBUG
#include "functions.h"
#endif // DEBUG
#include "map.h"
#include "matrix.h"
#include "pixel.h"
#include "unit.h"

using namespace fourFs;
using namespace logic;

Simulation::Simulation()
   : m_width(0)
   , m_height(0)
   , m_range(0)
   , m_frequency(0)
   , m_amplitude(0)
   , m_pace(0)
   , m_square(0)
   , m_smooth(0)
   , m_isRunning(false)
   , m_shouldRun(false)
   , m_lua(luaL_newstate())
{
   luaL_openlibs(m_lua);
}

Simulation::Simulation(const Simulation & simulation)
   : m_width(simulation.m_width)
   , m_height(simulation.m_height)
   , m_range(simulation.m_range)
   , m_frequency(simulation.m_frequency)
   , m_amplitude(simulation.m_amplitude)
   , m_pace(simulation.m_pace)
   , m_square(simulation.m_square)
   , m_smooth(simulation.m_smooth)
   , m_map(simulation.m_map)
   , m_units(simulation.m_units)
   , m_isRunning(false)
   , m_shouldRun(false)
   , m_lua(luaL_newstate())
{
   luaL_openlibs(m_lua);
}

Simulation::~Simulation()
{
   stop();
   // finalize the lua interpreter
   lua_close(m_lua);
}

void Simulation::operator =(const Simulation & simulation)
{
   stop();
   m_width = simulation.m_width;
   m_height = simulation.m_height;
   m_range = simulation.m_range;
   m_frequency = simulation.m_frequency;
   m_amplitude = simulation.m_amplitude;
   m_pace = simulation.m_pace;
   m_square = simulation.m_square;
   m_smooth = simulation.m_smooth;
   m_map = simulation.m_map;
   m_units = simulation.m_units;
}

bool Simulation::good() const
{
   return ((! m_map->empty()) && (! m_units.empty()));
}

bool Simulation::isRunning() const
{
   return m_isRunning && m_shouldRun;
}

bool Simulation::isPaused() const
{
   return m_isRunning && ! m_shouldRun;
}

bool Simulation::isStopped() const
{
   return ! m_isRunning;
}

unsigned & Simulation::width()
{
   return m_width;
}

const unsigned & Simulation::width() const
{
   return m_width;
}

unsigned & Simulation::height()
{
   return m_height;
}

const unsigned & Simulation::height() const
{
   return m_height;
}

double & Simulation::range()
{
   return m_range;
}

const double & Simulation::range() const
{
   return m_range;
}

unsigned & Simulation::frequency()
{
   return m_frequency;
}

const unsigned & Simulation::frequency() const
{
   return m_frequency;
}

double & Simulation::amplitude()
{
   return m_amplitude;
}

const double & Simulation::amplitude() const
{
   return m_amplitude;
}

unsigned & Simulation::pace()
{
   return m_pace;
}

const unsigned & Simulation::pace() const
{
   return m_pace;
}

unsigned & Simulation::square()
{
   return m_square;
}

const unsigned & Simulation::square() const
{
   return m_square;
}

unsigned & Simulation::smooth()
{
   return m_smooth;
}

const unsigned & Simulation::smooth() const
{
   return m_smooth;
}

sharedMap Simulation::map()
{
   return m_map;
}

sharedConstMap Simulation::map() const
{
   return m_map;
}

unitList Simulation::units()
{
   return m_units;
}

constUnitList Simulation::units() const
{
   constUnitList units;

   BOOST_FOREACH(sharedUnit unit, m_units)
   {
      units.push_back(unit);
   }

   return units;
}

void Simulation::options(unsigned width, unsigned height, double range,
                         unsigned frequency, double amplitude, unsigned pace,
                         unsigned square, unsigned smooth)
{
   m_width = width;
   m_height = height;
   m_range = range;
   m_frequency = frequency;
   m_amplitude = amplitude;
   m_pace = pace;
   m_square = square;
   m_smooth = smooth;
}

void Simulation::newMap()
{
   m_map = sharedMap(new Map(m_width, m_height, m_range, m_frequency,
                             m_amplitude, m_pace, m_square, m_smooth));
}

void Simulation::newMap(unsigned width, unsigned height, double range,
                        unsigned frequency, double amplitude, unsigned pace,
                        unsigned square, unsigned smooth)
{
   options(width, height, range, frequency, amplitude, pace, square, smooth);

   newMap();
}

void Simulation::addUnits(unsigned num)
{
   if (m_map->empty()) return;

   sharedMatrix matrix = m_map->matrix();

   boost::random::uniform_int_distribution<> xDist(0, matrix->width() - 1);
   boost::random::uniform_int_distribution<> yDist(0, matrix->height() - 1);

   // lock m_mutex ::RAII::
   boost::lock_guard< boost::mutex > guard(m_mutex);

   for (unsigned i = 0; i < num; i++)
   {
      logic::sharedUnit unit(new logic::Unit(1));
      m_units.push_back(unit);

      logic::pixelsList area = matrix->pixelsAroundPosition(xDist(rng), yDist(rng), 1);

      logic::pixelIterator it;
      for (it = area.begin(); it != area.end(); ++it)
      {
         unit->addPixel(* it);
         (* it)->addUnit(unit);
      }

   }
   // m_mutex unlocked here in ~guard()
}

void Simulation::deleteUnits(unsigned num)
{
   // lock m_mutex ::RAII::
   boost::lock_guard< boost::mutex > guard(m_mutex);

   if (num == 0)
   {
      m_units.clear();
   }
   else
   {
      for (unsigned i = 0; i < num; i++)
      {
         if (m_units.size() == 0) break;
         m_units.pop_front();
      }
   }
   // m_mutex unlocked here in ~guard()
}

void Simulation::resizeUnits(unsigned num)
{
   if (m_units.size() > num)
   {
      deleteUnits(m_units.size() - num);
   }
   else if (m_units.size() < num)
   {
      addUnits(num - m_units.size());
   }
}

void Simulation::start()
{
   if (good() && isStopped())
   {
      m_loopThread = boost::thread(& Simulation::runLoop, this);

      boost::lock_guard< boost::mutex > guard(m_mutex);
      m_shouldRun = true;
   }
}

void Simulation::pause()
{
   if (! isRunning()) return;

   {
	   boost::lock_guard< boost::mutex > guard(m_mutex);
	   m_shouldRun = false;
   }
   m_cond.notify_one();
}

void Simulation::resume()
{
   if (! isPaused()) return;

   {
      boost::lock_guard< boost::mutex > guard(m_mutex);
      m_shouldRun = true;
   }
   m_cond.notify_one();
}

void Simulation::stop()
{
   if (isStopped()) return;

   m_loopThread.interrupt();
   m_loopThread.join();
   m_shouldRun = false;
}

void Simulation::runLoop() // main while cycle, (god function)
{
   m_isRunning = true;

   BOOST_SCOPE_EXIT(& m_shouldRun, & m_isRunning)
   {
      m_shouldRun = false;
      m_isRunning = false;
      Logger() << "[Simulation] Stop.\n";
   } BOOST_SCOPE_EXIT_END

   Logger() << "[Simulation] Start.\n";

   // open lua script file
   luaL_dofile(m_lua, "Scripts/functions.lua");

   lua_getglobal(m_lua, "sum");
   double result = 0;
   if (lua_isfunction(m_lua, lua_gettop(m_lua)))
   {
      lua_pushinteger(m_lua, 14);
      lua_pushinteger(m_lua, 28);
      lua_call(m_lua, 2, 1);
      if (lua_isnumber(m_lua, lua_gettop(m_lua)))
      {
         result = lua_tonumber(m_lua, lua_gettop(m_lua));
      }
   }
   std::cout << result << std::endl;

   while (true)
   {
      boost::unique_lock<boost::mutex> lock(m_mutex);
      while (! m_shouldRun)
      {
         Logger() << "[Simulation] Pause.\n";
         m_cond.wait(lock);
         Logger() << "[Simulation] Resume.\n";

         // TODO: check if the lua script file is changed, and reload it
      }
      boost::this_thread::interruption_point();

      /*
       * Real computing stuff here!
       */

      BOOST_FOREACH(sharedUnit unit, m_units)
      {
         // move the unit

      }

      boost::this_thread::interruption_point();
   }

   Logger() << "[Simulation] End.\n";
}
