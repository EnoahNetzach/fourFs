/*
 * main.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>

#include "matrix.h"
#include "pixel.h"
#include "state.h"
#include "terrain.h"
#include "unit.h"
#include "utilities.hpp"

using namespace FourFs;

int main(int argc, char * argv[])
{
   // GLOBAL variables
   bool execTime = false;

   // MAP variables
   unsigned mapWidth;
   unsigned mapHeight;
   double mapRange;
   unsigned mapFrequency;
   double mapAmplitude;
   unsigned mapPace;
   unsigned mapSquare;
   unsigned mapSmooth;
   bool mapTime;

   { // Program options
      namespace po = boost::program_options;

      po::options_description genericOptions("Generic options");
      genericOptions.add_options()
                 ("help,h", "produce help message")
                 ("time,t", po::value< bool >(& execTime)->default_value(false),
                       "print execution time")
                 ("verbose", "produce verbose messages (overrides all)")
                 ("version,v", "print version string");
      po::options_description mapOptions("Map options");
      mapOptions.add_options()
                 ("map-amplitude", po::value< double >(& mapAmplitude)->default_value(1),
                       "set the mapAmplitude of the random generated mapHeight for each pixel")
                 ("map-frequency", po::value< unsigned >(& mapFrequency)->default_value(10),
                       "set the mapFrequency of changing a pixel mapHeight")
                 ("map-height", po::value< unsigned >(& mapHeight)->default_value(70),
                       "set the height")
                 ("map-length,l", po::value< unsigned >(),
                       "set <width> and <height> (produces a square map)")
                 ("map-pace", po::value< unsigned >(& mapPace)->default_value(10),
                       "set the pace between two selected pixels")
                 ("map-range", po::value< double >(& mapRange)->default_value(3),
                       "set the number of iterations used")
                 ("map-smooth", po::value< unsigned >(& mapSmooth)->default_value(4),
                       "set the square radius of pixels used for smoothing")
                 ("map-square", po::value< unsigned >(& mapSquare)->default_value(3),
                       "set the square radius of pixels changed")
                 ("map-time", po::value< bool >(& mapTime)->default_value(false),
                       "print map creation time")
                 ("map-width", po::value< unsigned >(& mapWidth)->default_value(100),
                       "set the width");

      po::options_description cmdlineOptions;
      cmdlineOptions.add(genericOptions).add(mapOptions);

      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, cmdlineOptions), vm);
      po::notify(vm);

      // GLOBAL options
      if (vm.count("help"))
      {
         std::cout << cmdlineOptions << std::endl;
         return 1;
      }

      // MAP options
      if (vm.count("map-length"))
      {
         mapWidth = vm["map-length"].as< unsigned >();
         mapHeight = vm["map-length"].as< unsigned >();
      }

      // verbose option overrides all
      if (vm.count("verbose"))
      {
         execTime = true;
         mapTime = true;
      }
   }

   boost::timer::cpu_timer timer;
   timer.start();

   Terrain terrain(mapWidth, mapHeight, mapRange, mapFrequency, mapAmplitude, mapPace, mapSquare, mapSmooth, mapTime);
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
   if (execTime)
   {
      std::string format = "Execution time:\n> %ws wall, %us user + %ss system = %ts CPU (%p%)";
      std::cout << timer.format(boost::timer::default_places, format) << std::endl;
   }

	return 0;
}
