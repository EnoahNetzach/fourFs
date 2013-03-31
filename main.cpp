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
   double range = 3;
   unsigned frequency = 10;
   double amplitude = 1;
   unsigned pace = 10;
   unsigned square = 3;
   unsigned smooth = 4;

   { // Program options
      namespace po = boost::program_options;

      po::options_description genericOptions("Generic options");
      genericOptions.add_options()
                 ("help,h", "produce help message")
                 ("version,v", "print version string");
      po::options_description mapOptions("Map options");
      mapOptions.add_options()
                 ("map-width", po::value< unsigned >(& width)->default_value(100),
                       "set the width")
                 ("map-height", po::value< unsigned >(& height)->default_value(70),
                       "set the height")
                 ("map-length,l", po::value< unsigned >(),
                       "set <width> and <height> (produces a square map)")
                 ("map-range", po::value< double >(& range)->default_value(3),
                       "set the number of iterations used")
                 ("map-frequency", po::value< unsigned >(& frequency)->default_value(10),
                       "set the frequency of changing a pixel height")
                 ("map-amplitude", po::value< double >(& amplitude)->default_value(1),
                       "set the amplitude of the random generated height for each pixel")
                 ("map-pace", po::value< unsigned >(& pace)->default_value(10),
                       "set the pace between two selected pixels")
                 ("map-square", po::value< unsigned >(& square)->default_value(3),
                       "set the square radius of pixels changed")
                 ("map-smooth", po::value< unsigned >(& smooth)->default_value(4),
                       "set the square radius of pixels used for smoothing");

      po::options_description cmdlineOptions;
      cmdlineOptions.add(genericOptions).add(mapOptions);

      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, cmdlineOptions), vm);
      po::notify(vm);

      if (vm.count("help"))
      {
         std::cout << cmdlineOptions << std::endl;
         return 1;
      }

      if (vm.count("map-length"))
      {
         width = vm["map-length"].as< unsigned >();
         height = vm["map-length"].as< unsigned >();
      }
   }

   Terrain terrain(width, height, range, frequency, amplitude, pace, square, smooth);
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
