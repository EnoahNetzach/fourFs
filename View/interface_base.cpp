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

Interface_base::Interface_base(bool time, const char * name)
   : m_good(false)
   , m_name(name)
   , m_time(time)
{
}

Interface_base::~Interface_base()
{
}

void Interface_base::initialize()
{
   boost::timer::cpu_timer timer;
   if (m_time) timer.start();

   initializeImpl();

   if (m_time)
   {
      timer.stop();
      std::string format = "View ";
      format += m_name;
      format += " initialization";
      std::cout << timer.format(boost::timer::default_places, timerFormat(format.c_str())) << std::endl;
   }
}

bool Interface_base::good() const
{
   return m_good;
}

void Interface_base::show(const logic::Map & map)
{
   boost::timer::cpu_timer timer;
   if (m_time) timer.start();

   showImpl(map.matrix());

   if (m_time)
   {
      timer.stop();
      std::string format = "View ";
      format += m_name;
      format +" show map";
      std::cout << timer.format(boost::timer::default_places, timerFormat(format.c_str())) << std::endl;
   }
}
