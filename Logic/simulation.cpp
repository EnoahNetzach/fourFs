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

#include "map.h"
#include "matrix.h"
#include "pixel.h"
#include "unit.h"


using namespace fourFs;
using namespace logic;

Simulation::Simulation()
   : m_isRunning(false)
   , m_shouldCompute(false)
{
}

Simulation::~Simulation()
{
   stop();
}

bool Simulation::good() const
{
   return ((! m_map->empty()) && (! m_units.empty()));
}

bool Simulation::isRunning() const
{
   return m_isRunning && m_shouldCompute;
}

bool Simulation::isPaused() const
{
   return m_isRunning && ! m_shouldCompute;
}

bool Simulation::isStopped() const
{
   return ! m_isRunning;
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

void Simulation::newMap(unsigned width, unsigned height, double range,
                        unsigned frequency, double amplitude, unsigned pace,
                        unsigned square, unsigned smooth)
{
   m_map = sharedMap(new Map(width, height, range, frequency,
                             amplitude, pace, square, smooth));
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
      logic::sharedUnit unit(new logic::Unit);
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
      m_shouldCompute = true;
   }
}

void Simulation::pause()
{
   if (! isRunning()) return;

   {
	   boost::lock_guard< boost::mutex > guard(m_mutex);
	   m_shouldCompute = false;
   }
   m_cond.notify_one();
   Logger() << "[Simulation] Pause.\n";
}

void Simulation::resume()
{
   if (! isPaused()) return;

   {
      boost::lock_guard< boost::mutex > guard(m_mutex);
      m_shouldCompute = true;
   }
   m_cond.notify_one();
   Logger() << "[Simulation] Resume.\n";
}

void Simulation::stop()
{
   if (isStopped()) return;

   m_loopThread.interrupt();
   m_loopThread.join();
   m_shouldCompute = true;
   Logger() << "[Simulation] Stop.\n";
}

void Simulation::runLoop() // main while cycle, (god function)
{
   m_isRunning = true;
   BOOST_SCOPE_EXIT(& m_isRunning)
   {
      m_isRunning = false;
   } BOOST_SCOPE_EXIT_END

   Logger() << "[Simulation] Start.\n";
   while (true)
   {
      boost::unique_lock<boost::mutex> lock(m_mutex);
      while (! m_shouldCompute)
      {
         std::cout << "idle" << std::endl;
         m_cond.wait(lock);
      }
      boost::this_thread::interruption_point();

      boost::chrono::nanoseconds sec(2500000);

      boost::this_thread::sleep_for(sec);

      boost::this_thread::interruption_point();
   }
   Logger() << "[Simulation] End.\n";
}
