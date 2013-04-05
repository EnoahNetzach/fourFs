/*
 * state.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "state.h"

using namespace fourFs;
using namespace logic;

State::State()
{
}

State::~State()
{
}

void State::addUnit(sharedUnit unit)
{
   m_units.push_back(unit);
}

bool State::removeUnit(sharedConstUnit unit)
{
   bool found = false;
   unitIterator it;

   for (it = m_units.begin(); it != m_units.end(); ++it)
   {
      if ((* it) == unit)
      {
         found = true;
         m_units.erase(it);
         break;
      }
   }

   return found;
}

void State::clearUnits()
{
   m_units.clear();
}

unitList & State::units()
{
   return m_units;
}
