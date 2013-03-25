/*
 * main.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include <iostream>

#include <boost/program_options.hpp>

#include "matrix.h"
#include "pixel.h"
#include "state.h"
#include "terrain.h"
#include "unit.h"
#include "utilities.hpp"

using namespace FourFs;

int main(int argc, char * argv[])
{
   unsigned width;
   unsigned height;

   { // Program options
      namespace po = boost::program_options;

      po::options_description desc("Allowed options");
      desc.add_options()
                 ("help,h", "produce help message")
                 ("width", po::value< unsigned >(& width), "set the map width")
                 ("height", po::value< unsigned >(& height), "set the map height");

      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, desc), vm);
      po::notify(vm);

      if (vm.count("help"))
      {
         std::cout << desc << std::endl;
         return 1;
      }
   }

   Terrain terrain(width, height);
   sharedMatrix matrix = terrain.matrix();

   sharedUnit unit1(new Unit);
   sharedUnit unit2(new Unit);
   sharedUnit unit3(new Unit);
   sharedUnit unit4(new Unit);

   pixelsList area1 = matrix.get()->pixelsAroundPosition(12, 2, 1);
   pixelsList area2 = matrix.get()->pixelsAroundPosition(13, 3, 1);
   pixelsList area3 = matrix.get()->pixelsAroundPosition(11, 2, 1);
   pixelsList area4 = matrix.get()->pixelsAroundPosition(11, 4, 1);

   pixelsIterator it;
   for (it = area1.begin(); it != area1.end(); ++it)
   {
      unit1.get()->addPixel(* it);
      (* it)->addUnit(unit1);
   }
   for (it = area2.begin(); it != area2.end(); ++it)
   {
      unit2.get()->addPixel(* it);
      (* it)->addUnit(unit2);
   }
   for (it = area3.begin(); it != area3.end(); ++it)
   {
      unit3.get()->addPixel(* it);
      (* it)->addUnit(unit3);
   }
   for (it = area4.begin(); it != area4.end(); ++it)
   {
      unit4.get()->addPixel(* it);
      (* it)->addUnit(unit4);
   }

   //terrain.show();

	return 0;
}
