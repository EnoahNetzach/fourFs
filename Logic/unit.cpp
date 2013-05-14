/**
 * @file unit.cpp
 *
 * @date Mar 20, 2013
 * @author Enoah Netzach
 */

#include "unit.h"

#include <iostream>

#include <boost/foreach.hpp>

#include "pixel.h"
#include "state.h"

using namespace fourFs;
using namespace logic;

Unit::Unit(id_type id, unsigned radius, double longevity,
           double fertility, double belligerance)
   : m_id(id)
   , m_radius(radius)
   , m_belligerance(belligerance)
   , m_fertility(fertility)
   , m_longevity(longevity)
   , m_centralPixel(0)
{
}

id_type Unit::id() const
{
   return m_id;
}

unsigned & Unit::radius()
{
   return m_radius;
}

const unsigned & Unit::radius() const
{
   return m_radius;
}

unsigned Unit::fieldOfView()
{
   return 5;
}

double Unit::longevity () const
{
   return m_longevity;
}

double Unit::fertility () const
{
   return m_fertility;
}

double Unit::belligerance () const
{
   return m_belligerance;
}

void Unit::addPixel(index_type index)
{
   m_pixels.push_back(index);
}

bool Unit::removePixel(index_type index)
{
   bool found = false;
   for (indexList::iterator it = m_pixels.begin(); it != m_pixels.end(); ++it)
   {
      if ((* it) == index)
      {
         found = true;
         m_pixels.erase(it);
         break;
      }
   }

   return found;
}

void Unit::clearPixels()
{
   m_pixels.clear();
}

bool Unit::hasPixel(index_type index)
{
   bool found = false;
   BOOST_FOREACH(index_type i, m_pixels)
   {
      if (i == index)
      {
         found = true;
         break;
      }
   }

   return found;
}

indexList Unit::pixels() const
{
   return m_pixels;
}

void Unit::centralPixel(index_type index)
{
   m_centralPixel = index;
}

index_type Unit::centralPixel() const
{
   return m_centralPixel;
}

//sharedState Unit::state()
//{
//   return m_state;
//}
//
//sharedConstState Unit::state() const
//{
//   return m_state;
//}
