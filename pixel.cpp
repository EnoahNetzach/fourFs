/*
 * pixel.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "pixel.h"

#include "environment.h"
#include "unit.h"

using namespace FourFs;

Pixel::Pixel(unsigned index)
   : m_index(index)
{

}

Pixel::~Pixel()
{
   // TODO Auto-generated destructor stub
}

unsigned Pixel::index () const
{
   return m_index;
}

double & Pixel::vivibility()
{
   return m_vivibility;
}

const double & Pixel::vivibility() const
{
   return m_vivibility;
}

bool Pixel::isBorder() const
{
   return m_border;
}

Environment & Pixel::environment()
{
   return * m_environment;
}

const Environment & Pixel::environment() const
{
   return * m_environment;
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

void Pixel::addUnit(Unit & unit)
{
   m_units.push_back(& unit);
}

bool Pixel::removeUnit(const Unit & unit)
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

void Pixel::clearUnits()
{
   m_units.clear();
}

unitsList & Pixel::units()
{
   return m_units;
}
