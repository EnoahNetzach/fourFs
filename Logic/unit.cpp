/*
 * unit.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "unit.h"

#include <iostream>

#include <boost/foreach.hpp>

#include "pixel.h"
#include "state.h"

using namespace fourFs;
using namespace logic;

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

Unit::Unit(unsigned radius)
   : m_radius(radius)
   , m_belligerance(0)
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
   weakPixelIterator it;

   for (it = m_pixels.begin(); it != m_pixels.end(); ++it)
   {
      if ((* it).lock() == pixel)
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

void Unit::centralPixel(sharedPixel pixel)
{
   m_centralPixel = pixel;
}

sharedPixel Unit::centralPixel()
{
   return m_centralPixel.lock();
}

const sharedConstPixel Unit::centralPixel() const
{
   return m_centralPixel.lock();
}

pixelList Unit::pixels()
{
   pixelList pixels;

   BOOST_FOREACH(weakPixel pixel, m_pixels)
   {
      pixels.push_back(pixel.lock());
   }

   return pixels;
}

const constPixelList Unit::pixels() const
{
   constPixelList pixels;

   BOOST_FOREACH(weakPixel pixel, m_pixels)
   {
      pixels.push_back(pixel.lock());
   }

   return pixels;
}

sharedState Unit::state()
{
   return m_state;
}

sharedConstState Unit::state() const
{
   return m_state;
}
