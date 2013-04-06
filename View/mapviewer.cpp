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

MapViewer::MapViewer(const Map & map, Options op, bool time)
   : m_map(map)
{
   if (op & terminal)
   {
      sharedInterface interface(new TerminalInterface(time));
      interface.get()->initialize();

      if (interface.get()->good())
      {
         m_interfaces.push_back(interface);
      }
   }

   if (op & openGL)
   {
      sharedInterface interface(new OpenGLInterface(time));
      interface.get()->initialize();

      if (interface.get()->good())
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
   BOOST_FOREACH(sharedInterface interface, m_interfaces)
   {
      interface.get()->showMap(m_map);
   }
}

void MapViewer::showUnits() const
{
   BOOST_FOREACH(sharedInterface interface, m_interfaces)
   {
      interface.get()->showUnits(m_map);
   }
}
