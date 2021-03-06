/*
 * mapviewer.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: Enoah Netzach
 */

#include "mapviewer.h"

#include <boost/foreach.hpp>

#include "../Logic/map.h"
#include "../Logic/pixel.h"
#include "interface_base.h"
#include "openglinterface.h"
#include "terminalinterface.h"

using namespace fourFs;
using namespace logic;
using namespace view;

MapViewer::MapViewer(Options op)
{
   if (op & terminal)
   {
      sharedInterface interface(new TerminalInterface);
      interface->initialize();

      if (interface->good())
      {
         m_interfaces.push_back(interface);
      }
   }

   if (op & openGL)
   {
      sharedInterface interface(new OpenGLInterface);
      interface->initialize();

      if (interface->good())
      {
         m_interfaces.push_back(interface);
      }
   }
}

MapViewer::~MapViewer()
{
}

void MapViewer::show(sharedConstMap map) const
{
   BOOST_FOREACH(sharedInterface interface, m_interfaces)
   {
      interface->show(map);
   }
}
