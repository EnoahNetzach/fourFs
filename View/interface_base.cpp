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

#include "../Logic/map.h"

using namespace fourFs;
using namespace logic;
using namespace view;

Interface_base::Interface_base(const char * name)
   : m_good(false)
   , m_name(name)
{
}

Interface_base::~Interface_base()
{
}

void Interface_base::initialize()
{
   boost::timer::cpu_timer timer;
   if (Logger::verbose()) timer.start();

   initializeImpl();

   if (Logger::verbose())
   {
      timer.stop();
      std::string format = "View ";
      format += m_name;
      format += " initialization";
      Logger() << timer.format(boost::timer::default_places, timerFormat(format.c_str())) << "\n";
   }
}

bool Interface_base::good() const
{
   return m_good;
}

void Interface_base::show(const logic::Map & map)
{
   boost::timer::cpu_timer timer;
   if (Logger::verbose()) timer.start();

   showImpl(map.matrix());

   if (Logger::verbose())
   {
      timer.stop();
      std::string format = "View ";
      format += m_name;
      format +" show map";
      Logger() << timer.format(boost::timer::default_places, timerFormat(format.c_str())) << "\n";
   }
}
