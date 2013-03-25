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
#include "pixel.h"
#include "unit.h"

using namespace FourFs;

Matrix::Matrix(unsigned width, unsigned height)
   : m_height(height)
   , m_width(width)
{
   for (unsigned i = 0; i < m_width * m_height; i++)
   {
      m_pixels.push_back(sharedPixel(new Pixel(i)));
   }
}

Matrix::~Matrix()
{
   // clear every reference to pixels
   BOOST_FOREACH(sharedPixel pixel, m_pixels)
   {
      // clear environments
      if (pixel->environment() != 0)
      {
         pixel->environment().get()->clearPixels();
      }

      // clear units
      BOOST_FOREACH(sharedUnit unit, pixel->units())
      {
         if (unit != 0) unit.get()->clearPixels();
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

unsigned Matrix::size() const
{
   return m_width * m_height;
}

sharedPixel Matrix::pixelAtIndex(unsigned index)
{
   return m_pixels.at(index);
}

sharedConstPixel Matrix::pixelAtIndex(unsigned index) const
{
   return m_pixels.at(index);
}

sharedPixel Matrix::pixelAtPosition(unsigned x, unsigned y)
{
   return pixelAtIndex(indexFromPosition(x, y));
}

sharedConstPixel Matrix::pixelAtPosition(unsigned x, unsigned y) const
{
   return pixelAtIndex(indexFromPosition(x, y));
}

pixelsList Matrix::pixelsAroundIndex(unsigned index, unsigned radius)
{
   std::pair< unsigned, unsigned > pos = positionFromIndex(index);

   return pixelsAroundPosition(pos.first, pos.second, radius);
}

const constPixelsList Matrix::pixelsAroundIndex(unsigned index, unsigned radius) const
{
   std::pair< unsigned, unsigned > pos = positionFromIndex(index);

   return pixelsAroundPosition(pos.first, pos.second, radius);
}

pixelsList Matrix::pixelsAroundPosition(unsigned x, unsigned y, unsigned radius)
{
   pixelsList pixels;

   for (int x1 = std::max(0, int(x) - int(radius));
        x1 <= std::min(int(m_width) - 1, int(x) + int(radius));
        x1++)
   {
      for (int y1 = std::max(0, int(y) - int(radius));
           y1 <= std::min(int(m_height) - 1, int(y) + int(radius));
           y1++)
      {
         pixels.push_back(pixelAtPosition(x1, y1));
      }
   }

   return pixels;
}

const constPixelsList Matrix::pixelsAroundPosition(unsigned x, unsigned y, unsigned radius) const
{
   constPixelsList pixels;

   for (int x1 = std::max(0, int(x) - int(radius));
        x1 <= std::min(int(m_width) - 1, int(x) + int(radius));
        x1++)
   {
      for (int y1 = std::max(0, int(y) - int(radius));
           y1 <= std::min(int(m_height) - 1, int(y) + int(radius));
           y1++)
      {
         pixels.push_back(pixelAtPosition(x1, y1));
      }
   }

   return pixels;
}
