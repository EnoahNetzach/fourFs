/*
 * viewer.cpp
 *
 *  Created on: Apr 20, 2013
 *      Author: Enoah Netzach
 */

#include "viewer.h"

#include <boost/foreach.hpp>

#include "terminalinterface.h"
#include "openglinterface.h"

using namespace fourFs;
using namespace interfaces;

Viewer::Viewer(logic::Simulation & simulation, Options op)
{
   if (op & terminal)
   {
      sharedInterface interface(new TerminalInterface(simulation));

      m_interfaces.push_back(interface);
   }

   if (op & openGL)
   {
//      sharedInterface interface(new OpenGLInterface);
//
//      if (interface->good())
//      {
//         m_interfaces.push_back(interface);
//      }
   }

   BOOST_FOREACH(sharedInterface interfaceSig, m_interfaces)
   {
      BOOST_FOREACH(sharedInterface interfaceSlot, m_interfaces)
      {
         interfaceSig->connect(interfaceSlot);
      }
   }
}

Viewer::~Viewer()
{
   BOOST_FOREACH(sharedInterface interface, m_interfaces)
   {
      interface->join();
   }
}

void Viewer::run()
{
   BOOST_FOREACH(sharedInterface interface, m_interfaces)
   {
      interface->run();
   }
}

void Viewer::join()
{
   BOOST_FOREACH(sharedInterface interface, m_interfaces)
   {
      interface->join();
   }
}

void Viewer::stop()
{
   BOOST_FOREACH(sharedInterface interface, m_interfaces)
   {
      interface->stop();
   }
}
