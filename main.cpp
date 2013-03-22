/*
 * main.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include <iostream>

#include "matrix.h"
#include "pixel.h"
#include "state.h"
#include "unit.h"

using namespace FourFs;

int main(int argc, char * argv[])
{
   Unit unit;

   for (unsigned i = 0; i < 10; ++i)
   {
      Pixel * p = new Pixel(i);
      p->test = i;

      unit.addPixel(* p);
   }

   Unit::pixelsIterator it;
   for (it = unit.pixelsBegin(); it != unit.pixelsEnd(); ++it)
   {
      std::cout << (* it)->test << std::endl;
   }

	return 0;
}

