/*
 * pixel.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "pixel.h"

using namespace FourFs;

Pixel::Pixel()
{
   // TODO Auto-generated constructor stub

}

Pixel::~Pixel()
{
   // TODO Auto-generated destructor stub
}

const unsigned & Pixel::position () const
{
   return m_position;
}

bool Pixel::isBorder() const
{
   return m_border;
}
