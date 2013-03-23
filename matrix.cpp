/*
 * matrix.cpp
 *
 *  Created on: Mar 22, 2013
 *      Author: Enoah Netzach
 */

#include "matrix.h"

#include <algorithm>
#include <iostream>

#include <boost/foreach.hpp>

#include "environment.h"
#include "unit.h"

using namespace FourFs;

Matrix::Matrix(unsigned width, unsigned height)
   : m_height(height)
   , m_width(width)
{
   for (unsigned i = 0; i < m_width * m_height; i++)
   {
      m_pixels.push_back(new Pixel(i));
   }
}

Matrix::~Matrix()
{
   // clear every reference to pixels
   BOOST_FOREACH(Pixel * pixel, m_pixels)
   {
      // clear environments
      pixel->environment().clearPixels();

      // clear units
      BOOST_FOREACH(Unit * unit, pixel->units())
      {
         unit->clearPixels();
      }
   }
}

unsigned Matrix::indexFromPosition(unsigned x, unsigned y) const
{
   return y * m_width + x;
}

std::pair< unsigned, unsigned > Matrix::positionFromIndex(unsigned index) const
{
   unsigned x = index % m_width;
   unsigned y = (index - x) / m_width;

   return std::make_pair(x, y);
}

unsigned Matrix::height() const
{
   return m_height;
}

unsigned Matrix::width() const
{
   return m_width;
}

Pixel & Matrix::pixelAtIndex(unsigned index)
{
   return * m_pixels.at(index);
}

Pixel & Matrix::pixelAtPosition(unsigned x, unsigned y)
{
   return pixelAtIndex(indexFromPosition(x, y));
}

pixelsList Matrix::pixelsAroundIndex(unsigned index)
{
   std::pair< unsigned, unsigned > pos = positionFromIndex(index);

   return pixelsAroundPosition(pos.first, pos.second);
}

/*
 * return a square of pixels around given (x, y), so (x+-r, y+-r)
 */
pixelsList Matrix::pixelsAroundPosition(unsigned x, unsigned y)
{
   pixelsList pixels;

   for (int x1 = std::max(0, int(x) - int(Unit::radius()));
        x1 <= std::min(int(m_width), int(x) + int(Unit::radius()));
        x1++)
   {
      for (int y1 = std::max(0, int(y) - int(Unit::radius()));
           y1 <= std::min(int(m_height), int(y) + int(Unit::radius()));
           y1++)
      {
         pixels.push_back(& pixelAtPosition(x1, y1));
      }
   }

   return pixels;
}

/*
 * debug pourpose
 */
void Matrix::print() const
{
   for (unsigned y = 0; y < m_height; y++)
   {
      for (unsigned x = 0; x < m_width; x++)
      {
         Pixel & pixel = * m_pixels.at(indexFromPosition(x, y));

         char c;
         if (pixel.isUnitsEmpty())
         {
            c = 'á';
         }
         else
         {
            c = 48 + pixel.nOfUnits();
         }
         std::cout << c << " ";
      }
      std::cout << "\n";
   }
   std::cout << std::flush;
}
