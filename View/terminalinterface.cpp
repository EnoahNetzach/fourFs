///*
// * terminal.cpp
// *
// *  Created on: Apr 5, 2013
// *      Author: Enoah Netzach
// */
//
//#include "terminalinterface.h"
//
//#include <iostream>
//
//#include "../logger.h"
//#include "../Logic/map.h"
//#include "../Logic/matrix.h"
//#include "../Logic/pixel.h"
//
//using namespace fourFs;
//using namespace logic;
//using namespace view;
//
//TerminalInterface::TerminalInterface()
//   : Interface_base("terminal")
//{
//}
//
//TerminalInterface::~TerminalInterface()
//{
//}
//
//void TerminalInterface::initializeImpl()
//{
//   m_good = std::cout.good();
//}
//
//void TerminalInterface::showImpl(sharedConstMatrix matrix)
//{
//   m_matrix = matrix;
//
//   if (good())
//   {
//      m_loopThread = boost::thread(& TerminalInterface::runLoop, this);
//   }
//}
//
//void TerminalInterface::runLoop()
//{
//   bool shouldReturn = false;
//   while (! shouldReturn)
//   {
//      std::cout << "[Term interface] What would you like to show? (Map, Units, Quit) " << std::flush;
//      std::string input;
//
//      do
//      {
//         std::cin >> input;
//
//         if (input == "m")
//         {
//            showMap(m_matrix.lock());
//         }
//         else if (input == "u")
//         {
//            showUnits(m_matrix.lock());
//         }
//         else if (input == "q")
//         {
//            shouldReturn = true;
//            break;
//         }
//      } while (std::cin.peek() != '\n');
//
//      std::cin.clear();
//   }
//}
//
//void TerminalInterface::showMap(sharedConstMatrix matrix)
//{
//   std::cout << "_MAP" << std::string(matrix->width() * 2 - 2, '_') << "\n";
//   for (unsigned y = 0; y < matrix->height(); y++)
//   {
//      std::cout << "|";
//      for (unsigned x = 0; x < matrix->width(); x++)
//      {
//         sharedConstPixel pixel = matrix->pixelAtPosition(x, y);
//         double height = pixel->height();
//
//         char c;
//         switch(int(height * 10))
//         {
//         case 0:
//            c = ' ';
//            break;
//         case 1:
//            c = '.';
//            break;
//         case 2:
//            c = ':';
//            break;
//         case 3:
//            c = '*';
//            break;
//         case 4:
//            c = 'o';
//            break;
//         case 5:
//            c = 'g';
//            break;
//         case 6:
//            c = '&';
//            break;
//         case 7:
//            c = '8';
//            break;
//         case 8:
//            c = '#';
//            break;
//         default:
//            c = '@';
//            break;
//         }
//         std::cout << c << c;
//      }
//      std::cout << "|" << std::endl;
//   }
//   std::cout << std::string(matrix->width() * 2 + 2, '^') << std::endl;
//}
//
//void TerminalInterface::showUnits(sharedConstMatrix matrix)
//{
//   std::cout << "_UNITS" << std::string(matrix->width() * 2 - 4, '_') << "\n";
//   for (unsigned y = 0; y < matrix->height(); y++)
//   {
//      std::cout << "|";
//      for (unsigned x = 0; x < matrix->width(); x++)
//      {
//         sharedConstPixel pixel = matrix->pixelAtPosition(x, y);
//
//         char c;
//         if (pixel->isUnitsEmpty())
//         {
//            c = '.';
//         }
//         else
//         {
//            c = 48 + pixel->nOfUnits();
//         }
//         std::cout << " " << c;
//      }
//      std::cout << "|\n";
//   }
//   std::cout << std::string(matrix->width() * 2 + 2, '^') << std::endl;
//}
