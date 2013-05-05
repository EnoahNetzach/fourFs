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

using namespace fourFs;
using namespace logic;

Matrix::Matrix(unsigned width, unsigned height)
   : m_height(height)
   , m_width(width)
{
   for (index_type i = 0; i < m_width * m_height; i++)
   {
      m_pixels.push_back(sharedPixel(new Pixel(i + 1)));
   }
}

Matrix::~Matrix()
{
   // clear every reference to pixels
   BOOST_FOREACH(sharedPixel pixel, m_pixels)
   {
      // clear environments
//      if (pixel->environment() != 0)
//      {
//         pixel->environment()->clearPixels();
//      }
   }

}

index_type Matrix::indexFromPosition(unsigned x, unsigned y) const
{
   return y * m_width + x;
}

Matrix::coordinates Matrix::positionFromIndex(index_type index) const
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

sharedPixel Matrix::pixelAtIndex(index_type index)
{
   return m_pixels.at(index);
}

const sharedConstPixel Matrix::pixelAtIndex(index_type index) const
{
   return m_pixels.at(index);
}

sharedPixel Matrix::pixelAtPosition(unsigned x, unsigned y)
{
   return pixelAtIndex(indexFromPosition(x, y));
}

const sharedConstPixel Matrix::pixelAtPosition(unsigned x, unsigned y) const
{
   return pixelAtIndex(indexFromPosition(x, y));
}

pixelList Matrix::pixelsAroundIndex(index_type index, unsigned radius)
{
   std::pair< unsigned, unsigned > pos = positionFromIndex(index);

   return pixelsAroundPosition(pos.first, pos.second, radius);
}

const constPixelList Matrix::pixelsAroundIndex(index_type index, unsigned radius) const
{
   std::pair< unsigned, unsigned > pos = positionFromIndex(index);

   return pixelsAroundPosition(pos.first, pos.second, radius);
}

pixelList Matrix::pixelsAroundPosition(unsigned x, unsigned y, unsigned radius)
{
   pixelList pixels;

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

const constPixelList Matrix::pixelsAroundPosition(unsigned x, unsigned y, unsigned radius) const
{
   constPixelList pixels;

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
