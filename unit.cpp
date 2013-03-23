/*
 * unit.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "unit.h"

#include "pixel.h"
#include "state.h"

using namespace FourFs;

Unit::Unit()
{
}

Unit::~Unit()
{
   // TODO Auto-generated destructor stub
}

unsigned Unit::longevity () const
{
   return m_longevity;
}

unsigned Unit::fertility () const
{
   return m_fertility;
}

unsigned Unit::belligerance () const
{
   return m_belligerance;
}

void Unit::addPixel(Pixel & pixel)
{
   m_pixels.push_back(& pixel);
}

bool Unit::removePixel(Pixel & pixel)
{
   bool found = false;
   pixelsIterator it;

   for (it = m_pixels.begin(); it != m_pixels.end(); ++it)
   {
      if ((* it) == & pixel)
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

pixelsConstIterator Unit::pixelsBegin() const
{
   return m_pixels.begin();
}

pixelsConstIterator Unit::pixelsEnd() const
{
   return m_pixels.end();
}

State & Unit::state()
{
   return * m_state;
}

const State & Unit::state() const
{
   return * m_state;
}
