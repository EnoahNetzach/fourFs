/*
 * interface_base.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: Enoah Netzach
 */

#include "interface_base.h"

#include <iostream>
#include <string>

#include <boost/timer/timer.hpp>

#include "../logger.h"
#include "../Logic/map.h"
#include "../Logic/simulation.h"

using namespace fourFs;
using namespace logic;
using namespace interfaces;

Interface_base::Interface_base(const char * name, logic::Simulation & simulation)
   : m_simulation(simulation)
   , m_name(name)
{
}

Interface_base::~Interface_base()
{
   BOOST_FOREACH(connection_type conn, m_showMapConnections)
   {
      conn.disconnect();
   }
   BOOST_FOREACH(connection_type conn, m_showUnitsConnections)
   {
      conn.disconnect();
   }

   stop();
}

void Interface_base::run()
{
   m_runThread = boost::thread(& Interface_base::runImpl, this);
}

void Interface_base::stop()
{
   interrupt();
   join();
}

void Interface_base::interrupt()
{
   m_runThread.interrupt();
}

void Interface_base::join()
{
   m_runThread.join();
}

void Interface_base::connect(sharedInterface interface)
{
   m_showMapConnections.push_back(interface->connectShowMap(boost::bind(& Interface_base::showMap, this)));
   m_showUnitsConnections.push_back(interface->connectShowUnits(boost::bind(& Interface_base::showUnits, this)));
}

void Interface_base::showMap() const
{
   showMapImpl(m_simulation.map()->matrix());
}

void Interface_base::showUnits() const
{
   showUnitsImpl(m_simulation.map()->matrix());
}

void Interface_base::callShowMap() const
{
   m_showMapSignal();
}

void Interface_base::callShowUnits() const
{
   m_showUnitsSignal();
}

Interface_base::connection_type Interface_base::connectShowMap(const showSignal_type::slot_type & slot)
{
   return m_showMapSignal.connect(slot);
}

Interface_base::connection_type Interface_base::connectShowUnits(const showSignal_type::slot_type & slot)
{
   return m_showUnitsSignal.connect(slot);
}
