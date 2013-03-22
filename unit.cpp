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
   // TODO Auto-generated constructor stub
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

void Unit::addPixel(const Pixel & pixel)
{
   m_pixels.push_back(& pixel);
}

void Unit::removePixel(const Pixel & pixel)
{
   pixelsList::iterator it;

   for (it = m_pixels.begin(); it != m_pixels.end(); ++it)
   {
      if ((* it) == & pixel) m_pixels.erase(it);
   }
}

void Unit::clearPixels()
{
   m_pixels.clear();
}

Unit::pixelsIterator Unit::pixelsBegin() const
{
   return m_pixels.begin();
}

Unit::pixelsIterator Unit::pixelsEnd() const
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
