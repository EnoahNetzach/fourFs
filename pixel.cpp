/*
 * pixel.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "pixel.h"

using namespace FourFs;

Pixel::Pixel(unsigned index)
   : m_index(index)
{
   // TODO Auto-generated constructor stub

}

Pixel::~Pixel()
{
   // TODO Auto-generated destructor stub
}

unsigned Pixel::index () const
{
   return m_index;
}

bool Pixel::isBorder() const
{
   return m_border;
}
