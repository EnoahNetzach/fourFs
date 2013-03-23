/*
 * state.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "state.h"

using namespace FourFs;

State::State()
{
}

State::~State()
{
}

void State::addUnit(Unit & unit)
{
   m_units.push_back(& unit);
}

bool State::removeUnit(const Unit & unit)
{
   bool found = false;
   unitsIterator it;

   for (it = m_units.begin(); it != m_units.end(); ++it)
   {
      if ((* it) == & unit)
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

unitsList & State::units()
{
   return m_units;
}
