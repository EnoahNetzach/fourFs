/*
 * terminal.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#include "terminalinterface.h"

#include <iostream>

#include "../Logic/map.h"
#include "../Logic/pixel.h"

using namespace fourFs;
using namespace logic;
using namespace view;

TerminalInterface::TerminalInterface(bool time)
   : Interface_base(time, "terminal")
{
}

TerminalInterface::~TerminalInterface()
{
}

void TerminalInterface::initializeImpl()
{
   m_good = std::cout.good();
}

void TerminalInterface::showMapImpl(const logic::Map & map) const
{
   std::cout << std::string(map.matrix().get()->width() * 2 + 2, '-') << "\n";
   for (unsigned y = 0; y < map.matrix().get()->height(); y++)
   {
      std::cout << "|";
      for (unsigned x = 0; x < map.matrix().get()->width(); x++)
      {
         sharedConstPixel pixel = map.matrix().get()->pixelAtPosition(x, y);

         double height = pixel.get()->height();

         char c;
         if (height < 0.1)
         {
            c = ' ';
         }
         else if (height < 0.2)
         {
            c = '.';
         }
         else if (height < 0.3)
         {
            c = ':';
         }
         else if (height < 0.4)
         {
            c = '*';
         }
         else if (height < 0.5)
         {
            c = 'o';
         }
         else if (height < 0.6)
         {
            c = 'g';
         }
         else if (height < 0.7)
         {
            c = '&';
         }
         else if (height < 0.8)
         {
            c = '8';
         }
         else if (height < 0.9)
         {
            c = '#';
         }
         else
         {
            c = '@';
         }
         std::cout << c << c;
      }
      std::cout << "|\n";
   }
   std::cout << std::string(map.matrix().get()->width() * 2 + 2, '-') << std::endl;
}

void TerminalInterface::showUnitsImpl(const logic::Map & map) const
{
   std::cout << std::string(map.matrix().get()->width() * 2 + 2, '-') << "\n";
   for (unsigned y = 0; y < map.matrix().get()->height(); y++)
   {
      std::cout << "|";
      for (unsigned x = 0; x < map.matrix().get()->width(); x++)
      {
         sharedConstPixel pixel = map.matrix().get()->pixelAtPosition(x, y);

         char c;
         if (pixel.get()->isUnitsEmpty())
         {
            c = '.';
         }
         else
         {
            c = 48 + pixel.get()->nOfUnits();
         }
         std::cout << " " << c;
      }
      std::cout << "|\n";
   }
   std::cout << std::string(map.matrix().get()->width() * 2 + 2, '-') << std::endl;
}
