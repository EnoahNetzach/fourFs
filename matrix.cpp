/*
 * matrix.cpp
 *
 *  Created on: Mar 22, 2013
 *      Author: Enoah Netzach
 */

#include <algorithm>
#include <iostream>

#include "matrix.h"

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
   // TODO Auto-generated destructor stub
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
 * return a square of pixels around given (x, y), so (x+-1, y+-1)
 */
pixelsList Matrix::pixelsAroundPosition(unsigned x, unsigned y)
{
   pixelsList pixels;

   for (unsigned x1 = std::max(0, int(x) - 1); x1 <= std::min(int(m_width), int(x) + 1); x1++)
   {
      for (unsigned y1 = std::max(0, int(y) - 1); y1 <= std::min(int(m_height), int(y) + 1); y1++)
      {
         pixels.push_back(& pixelAtPosition(x1, y1));
      }
   }

   return pixels;
}

void Matrix::print() const
{
   for (unsigned y = 0; y < m_height; y++)
   {
      for (unsigned x = 0; x < m_width; x++)
      {

      }
      std::cout << "\n";
   }
   std::cout << std::flush;
}
