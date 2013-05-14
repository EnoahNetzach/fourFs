/*
 * swarm.cpp
 *
 *  Created on: May 1, 2013
 *      Author: Enoah Netzach
 */

#include "swarm.h"

#include <boost/foreach.hpp>

#include "unit.h"

using namespace fourFs;
using namespace logic;

Swarm::Swarm()
   : m_nextId(1)
{
}

unsigned Swarm::size() const
{
   return m_units.size();
}

bool Swarm::empty() const
{
   return m_units.empty();
}

sharedUnit Swarm::addUnit(unsigned radius, double longevity,
                      double fertility, double belligerance)
{
   sharedUnit unit(new Unit(m_nextId, radius, longevity,
                            fertility, belligerance));
   m_units.insert(std::make_pair(unit->id(), unit));
   m_nextId++;
   return unit;
}

bool Swarm::removeUnit(id_type id)
{
   bool found = false;
   std::map< id_type, sharedUnit >::iterator it = m_units.find(id);
   if (it != m_units.end())
   {
      m_units.erase(it);
      found = true;
   }

   return found;
}

indexList Swarm::deleteUnits(unsigned num)
{
   if (num == 0 || num > m_units.size()) num = m_units.size();

   indexList deleted;

   for (unsigned i = 0; i < num; i++)
   {
      deleted.push_back(m_units.begin()->first);
      m_units.erase(m_units.begin());
   }

   return deleted;
}

indexList Swarm::clearUnits()
{
   return deleteUnits(0);
}

sharedUnit Swarm::unitFromId(id_type id)
{
   return m_units.at(id);
}

const sharedConstUnit Swarm::unitFromId(id_type id) const
{
   return m_units.at(id);
}

unitMap Swarm::units()
{
   return m_units;
}
