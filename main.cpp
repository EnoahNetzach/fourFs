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

   Unit unit1, unit2;

   pixelsList area1 = matrix.pixelsAroundPosition(6, 14);
   pixelsList area2 = matrix.pixelsAroundPosition(15, 2);

   pixelsIterator it;
   for (it = area1.begin(); it != area1.end(); ++it)
   {
//      unit1.addPixel(* it); // TODO resolve
   }
   for (it = area2.begin(); it != area2.end(); ++it)
   {
//      unit2.addPixel(* it); // TODO resolve
   }

	return 0;
}

