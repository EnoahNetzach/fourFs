/*
 * pixel.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "pixel.h"

#include <iostream>

#include <boost/foreach.hpp>

#include "environment.h"
#include "unit.h"

using namespace fourFs;
using namespace logic;

Pixel::Pixel(unsigned index, bool border)
   : m_index(index)
   , m_height(0)
   , m_border(border)
{
}

Pixel::~Pixel()
{
}

unsigned Pixel::index () const
{
   return m_index;
}

double & Pixel::height()
{
   return m_height;
}

const double & Pixel::height() const
{
   return m_height;
}

bool Pixel::isBorder() const
{
   return m_border;
}

bool Pixel::isUnitsEmpty() const
{
   return m_units.empty();
}

bool Pixel::isUnitsUnique() const
{
   return m_units.size() <= 1;
}

unsigned Pixel::nOfUnits() const
{
   return m_units.size();
}

void Pixel::addUnit(id_type id)
{
   m_units.push_back(id);
}

bool Pixel::removeUnit(id_type id)
{
   bool found = false;
   for (idList::iterator it = m_units.begin(); it != m_units.end(); ++it)
   {
      if ((* it) == id)
      {
         found = true;
         m_units.erase(it);
         break;
      }
   }

   return found;
}

void Pixel::clearUnits()
{
   m_units.clear();
}

bool Pixel::hasUnit(id_type id)
{
   bool found = false;
   BOOST_FOREACH(id_type i, m_units)
   {
      if (i == id)
      {
         found = true;
         break;
      }
   }

   return found;
}

idList Pixel::units() const
{
   return m_units;
}

//sharedEnvironment Pixel::environment()
//{
//   return m_environment;
//}
//
//sharedConstEnvironment Pixel::environment() const
//{
//   return m_environment;
//}
