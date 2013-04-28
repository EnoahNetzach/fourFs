/*
 * simulation.cpp
 *
 *  Created on: Apr 11, 2013
 *      Author: Enoah Netzach
 */

#include "simulation.h"

#include <boost/chrono.hpp>
#include <boost/foreach.hpp>
#include <boost/random.hpp>
#include <boost/scope_exit.hpp>
#include <boost/make_shared.hpp>

#include "../logger.h"
#include "../Scripts/classes.hpp"
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
   , m_shouldReloadScript(false)
{
   // start the python interpreter
   Py_Initialize();
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
   , m_shouldReloadScript(false)
{
   // start the python interpreter
   Py_Initialize();
}

Simulation::~Simulation()
{
   stop();
   // stop the python interpreter
   Py_Finalize();
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

const constUnitList Simulation::units() const
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
   boost::lock_guard< boost::mutex > lock(m_mutex);

   for (unsigned i = 0; i < num; i++)
   {
      logic::sharedUnit unit(new logic::Unit(1));
      m_units.push_back(unit);

      unsigned x = xDist(rng);
      unsigned y = yDist(rng);

      logic::pixelList area = matrix->pixelsAroundPosition(x, y, 1);
      unit->centralPixel(matrix->pixelAtPosition(x, y));

      BOOST_FOREACH(sharedPixel pixel, area)
      {
         unit->addPixel(pixel);
         pixel->addUnit(unit);
      }
   }
}

void Simulation::deleteUnits(unsigned num)
{
   // lock m_mutex ::RAII::
   boost::lock_guard< boost::mutex > lock(m_mutex);

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

      boost::lock_guard< boost::mutex > lock(m_mutex);
      m_shouldRun = true;
   }
}

void Simulation::pause()
{
   if (! isRunning()) return;

   {
	   boost::lock_guard< boost::mutex > lock(m_mutex);
	   m_shouldRun = false;
   }
   m_cond.notify_one();
}

void Simulation::resume()
{
   if (! isPaused()) return;

   {
      boost::lock_guard< boost::mutex > lock(m_mutex);
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

void Simulation::reloadScript()
{
   boost::lock_guard< boost::mutex > lock(m_mutex);
   m_shouldReloadScript = true;
}

void Simulation::runLoop()
{
   m_isRunning = true;

   BOOST_SCOPE_EXIT(& m_shouldRun, & m_isRunning)
   {
      m_shouldRun = false;
      m_isRunning = false;
      Logger() << "[Simulation] Stop.\n";
   } BOOST_SCOPE_EXIT_END

   Logger() << "[Simulation] Start.\n";

   initfourFs();
   boost::python::object main = boost::python::import("__main__");
   boost::python::object gloabl(main.attr("__dict__"));
   boost::python::exec_file("Scripts/functions.py", gloabl, gloabl);

   bool runOnce = false;

   while (true)
   {
      {
         boost::unique_lock< boost::mutex > wait_lock(m_mutex);
         while (! m_shouldRun)
         {
            Logger() << "[Simulation] Pause.\n";
            m_cond.wait(wait_lock);
            Logger() << "[Simulation] Resume.\n";
         }
      }

      boost::this_thread::interruption_point();

      if (m_shouldReloadScript)
      {
         boost::lock_guard< boost::mutex > lock(m_mutex);
         boost::python::exec_file("Scripts/functions.py", gloabl, gloabl);

         Logger() << "[Simulation] Script reloaded.\n";

         m_shouldReloadScript = false;
      }

      boost::this_thread::interruption_point();

      /*
       * Real computing stuff here!
       */
      if (! runOnce)
      {
         try
         {
            boost::python::object help = gloabl["printHelp"];
            if(! help.is_none())
            {
               boost::lock_guard< boost::mutex > lock(m_mutex);
               help();
            }
         }
         catch (boost::python::error_already_set & e)
         {
            PyErr_Print();
            pause();
            continue;
         }
         catch(...)
         {
            std::cerr << "Something wrong occurred\n";
            pause();
            continue;
         }
      }

      try
      {
         boost::python::object function = gloabl["simulation"];
         if(! function.is_none())
         {
            boost::lock_guard< boost::mutex > lock(m_mutex);
            function(boost::python::ptr(m_map.get()), & m_units);
         }
      }
      catch (boost::python::error_already_set & e)
      {
         PyErr_Print();
         pause();
         continue;
      }
      catch(...)
      {
         std::cerr << "Something wrong occurred\n";
         pause();
         continue;
      }

      runOnce = true;

      boost::this_thread::interruption_point();
   }

   Logger() << "[Simulation] End.\n";
}
