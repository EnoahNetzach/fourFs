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
#include "utilities.hpp"

using namespace FourFs;

int main(int argc, char * argv[])
{
   Matrix matrix(20, 20);

   Unit unit1, unit2, unit3;

   pixelsList area1 = matrix.pixelsAroundPosition(6, 14);
   pixelsList area2 = matrix.pixelsAroundPosition(15, 2);
   pixelsList area3 = matrix.pixelsAroundPosition(0, 1);

   pixelsIterator it;
   for (it = area1.begin(); it != area1.end(); ++it)
   {
      unit1.addPixel(** it);
      (* it)->addUnit(unit1);
   }
   for (it = area2.begin(); it != area2.end(); ++it)
   {
      unit2.addPixel(** it);
      (* it)->addUnit(unit2);
   }
   for (it = area3.begin(); it != area3.end(); ++it)
   {
      unit3.addPixel(** it);
      (* it)->addUnit(unit3);
   }

   matrix.print();

	return 0;
}

