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
#include "terrain.h"
#include "unit.h"
#include "utilities.hpp"

using namespace FourFs;

int main(int argc, char * argv[])
{
   Terrain terrain(50, 19);
   Matrix & matrix = terrain.matrix();

   Unit unit1, unit2, unit3, unit4;

   pixelsList area1 = matrix.pixelsAroundPosition(42, 2);
   pixelsList area2 = matrix.pixelsAroundPosition(43, 3);
   pixelsList area3 = matrix.pixelsAroundPosition(41, 3);
   pixelsList area4 = matrix.pixelsAroundPosition(41, 4);

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
   for (it = area4.begin(); it != area4.end(); ++it)
   {
      unit4.addPixel(** it);
      (* it)->addUnit(unit4);
   }

   terrain.show();

	return 0;
}
