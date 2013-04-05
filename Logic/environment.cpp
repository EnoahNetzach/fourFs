/*
 * environment.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "environment.h"

using namespace fourFs;
using namespace logic;

Environment::Environment()
   : m_vivibility(-1)
{
}

Environment::~Environment()
{
}

double Environment::vivibility()
{
   return m_vivibility;
}


void Environment::addPixel(sharedPixel pixel)
{
   m_pixels.push_back(pixel);
}

bool Environment::removePixel(sharedPixel pixel)
{
   bool found = false;
   pixelIterator it;

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

void Environment::clearPixels()
{
   m_pixels.clear();
}

pixelConstIterator Environment::pixelsBegin() const
{
   return m_pixels.begin();
}

pixelConstIterator Environment::pixelsEnd() const
{
   return m_pixels.end();
}
