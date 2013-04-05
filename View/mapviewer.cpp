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

MapViewer::MapViewer(const Map & map, Options op)
   : m_map(map)
{
   if (op & terminal)
   {
      Interface_base * interface(TerminalInterface::instance());
      interface->initialize();

      if (interface->good())
      {
         m_interfaces.push_back(interface);
      }
   }

   if (op & openGL)
   {
      Interface_base * interface(OpenGLInterface::instance());
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

void MapViewer::showMap() const
{
   BOOST_FOREACH(Interface_base * interface, m_interfaces)
   {
      interface->showMap(m_map);
   }
}

void MapViewer::showUnits() const
{
   BOOST_FOREACH(Interface_base * interface, m_interfaces)
   {
      interface->showUnits(m_map);
   }
}
