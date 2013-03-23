/*
 * pixel.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "pixel.h"

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

bool Pixel::isBorder() const
{
   return m_border;
}

bool Pixel::isEmpty() const
{
   return m_units.empty();
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

// TODO clear

unitsList Pixel::units()
{
   return m_units;
}
