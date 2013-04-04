/*
 * unit.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "unit.h"

#include <iostream>

#include "pixel.h"
#include "state.h"

using namespace FourFs;

// STATIC members
unsigned Unit::radius()
{
   return 1;
}

unsigned Unit::fieldOfView()
{
   return 5;
}

Unit::Unit()
   : m_belligerance(0)
   , m_fertility(0)
   , m_longevity(0)
{
}

Unit::~Unit()
{
}

const double & Unit::longevity () const
{
   return m_longevity;
}

const double & Unit::fertility () const
{
   return m_fertility;
}

const double & Unit::belligerance () const
{
   return m_belligerance;
}

void Unit::addPixel(sharedPixel pixel)
{
   m_pixels.push_back(pixel);
}

bool Unit::removePixel(sharedPixel pixel)
{
   bool found = false;
   pixelsIterator it;

   for (it = m_pixels.begin(); it != m_pixels.end(); ++it)
   {
      if ((* it) == pixel)
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

sharedState Unit::state()
{
   return m_state;
}

sharedConstState Unit::state() const
{
   return m_state;
}
