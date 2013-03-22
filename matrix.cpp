/*
 * matrix.cpp
 *
 *  Created on: Mar 22, 2013
 *      Author: Enoah Netzach
 */

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

unsigned Matrix::indexFromPosition(unsigned x, unsigned y)
{
   return y * m_width + x;
}

std::pair< unsigned, unsigned > Matrix::positionFromIndex(unsigned index)
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
   return * m_pixels.at(indexFromPosition(x, y));
}
