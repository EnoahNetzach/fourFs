/*
 * main.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include <iostream>

#include <boost/program_options.hpp>
#include <boost/timer/timer.hpp>

#include "fourfs"

using namespace fourFs;

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
   bool mapTime = false;

   // SIMULATION options
   unsigned epochs;
   unsigned nOfUnits;

   // VIEW options
   interfaces::Options viewFlags = 0;

   { // Program options BEGIN
      namespace po = boost::program_options;

      po::options_description genericOptions("Generic options");
      genericOptions.add_options()
            ("help,h", "produce help message")
            ("silent,s", "suppress all messages")
            ("verbose,v", "produce verbose messages")
            ("version,V", "print version string");
      po::options_description mapOptions("Map options");
      mapOptions.add_options()
            ("map-amplitude", po::value< double >(& mapAmplitude)->default_value(1),
                  "set the amplitude of the random generated mapHeight for each pixel")
            ("map-frequency", po::value< unsigned >(& mapFrequency)->default_value(10),
                  "set the frequency of changing a pixel's height")
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
            ("map-width", po::value< unsigned >(& mapWidth)->default_value(100),
                  "set the width");
      po::options_description simulationOptions("Simulation options");
      simulationOptions.add_options()
            ("epochs,e", po::value< unsigned >(& epochs)->default_value(3000),
                  "set the number of life computations")
            ("units,u", po::value< unsigned >(& nOfUnits)->default_value(10),
                  "set the number of units to be used (might change during execution)");
      po::options_description viewOptions("View options");
      viewOptions.add_options()
            ("view-openGL,A", "show images with openGL")
            ("view-terminal,B", "show images in terminal")
            ("view-none,C", "suppress images showing");

      po::options_description cmdlineOptions;
      cmdlineOptions.add(genericOptions).add(mapOptions).add(simulationOptions).add(viewOptions);

      po::variables_map vm;
      po::store(po::parse_command_line(argc, argv, cmdlineOptions), vm);
      po::notify(vm);

      // GLOBAL options
      if (vm.count("help"))
      {
         std::cout << cmdlineOptions << std::endl;
         return 0;
      }
      if (vm.count("version"))
      {
         std::cout << "fourFs version 0.0" << std::endl;
         return 0;
      }
      if (vm.count("time"))
      {
         execTime = true;
      }

      // MAP options
      if (vm.count("map-length"))
      {
         mapWidth = vm["map-length"].as< unsigned >();
         mapHeight = vm["map-length"].as< unsigned >();
      }
      if (vm.count("map-time"))
      {
         mapTime = true;
      }

      // VIEW options
      if (vm.count("openGL"))
      {
         viewFlags |= interfaces::openGL;
      }
      if (vm.count("view-terminal"))
      {
         viewFlags |= interfaces::terminal;
      }
      if (vm.count("view-none"))
      {
         viewFlags &= ~(interfaces::openGL | interfaces::terminal);
      }

      // verbose option overrides all
      if (vm.count("verbose"))
      {
         Logger::verbose(true);
      }
   } // Program options END

   boost::timer::cpu_timer timer;
   if (Logger::verbose()) timer.start();

   // execution loop
   logic::Simulation simulation;
   simulation.newMap(mapWidth, mapHeight, mapRange, mapFrequency,
                     mapAmplitude, mapPace, mapSquare, mapSmooth);
   simulation.addUnits(nOfUnits);

   interfaces::Viewer viewer(simulation, viewFlags);
   viewer.run();

   viewer.join();

   if (Logger::verbose())
   {
      timer.stop();
      Logger() << timer.format(boost::timer::default_places, timerFormat("Execution")) << "\n";
   }

   return 0;
}
