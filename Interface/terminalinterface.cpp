/*
 * terminal.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#include "terminalinterface.h"

#include <iostream>

#include "../logger.h"
#include "../Logic/map.h"
#include "../Logic/matrix.h"
#include "../Logic/pixel.h"
#include "../Logic/simulation.h"

using namespace fourFs;
using namespace logic;
using namespace interfaces;

TerminalInterface::TerminalInterface(logic::Simulation & simulation)
   : Interface_base("terminal", simulation)
{
}

void TerminalInterface::runImpl()
{
   std::string input = "";

   do
   {
      input.clear();
      std::cout << "What would you like to do? (_s_how, _p_lay, p_a_use, s_t_op, _q_uit) " << std::flush;
      std::cin >> input;

      if (input == "s")
      {
         input.clear();
         std::cout << "[Term interface] What would you like to show? (_m_ap, _u_nits, _c_ancel) " << std::flush;
         std::cin >> input;

         if (input == "c") continue;
         if (input == "m") callShowMap();
         if (input == "u") callShowUnits();
      }
      if (input == "p")
      {
         if (m_simulation.isStopped()) m_simulation.start();
      }
      if (input == "a")
      {
         m_simulation.pause();
      }
      if (input == "t")
      {
         m_simulation.stop();
      }

      boost::this_thread::interruption_point();
   } while (input != "q");
}

void TerminalInterface::showMapImpl(sharedConstMatrix matrix) const
{
   std::cout << "_MAP" << std::string(matrix->width() * 2 - 2, '_') << "\n";
   for (unsigned y = 0; y < matrix->height(); y++)
   {
      std::cout << "|";
      for (unsigned x = 0; x < matrix->width(); x++)
      {
         sharedConstPixel pixel = matrix->pixelAtPosition(x, y);
         double height = pixel->height();

         char c;
         switch(int(height * 10))
         {
         case 0:
            c = ' ';
            break;
         case 1:
            c = '.';
            break;
         case 2:
            c = ':';
            break;
         case 3:
            c = '*';
            break;
         case 4:
            c = 'o';
            break;
         case 5:
            c = 'g';
            break;
         case 6:
            c = '&';
            break;
         case 7:
            c = '8';
            break;
         case 8:
            c = '#';
            break;
         default:
            c = '@';
            break;
         }
         std::cout << c << c;
      }
      std::cout << "|" << std::endl;
   }
   std::cout << std::string(matrix->width() * 2 + 2, '^') << std::endl;
}

void TerminalInterface::showUnitsImpl(sharedConstMatrix matrix) const
{
   std::cout << "_UNITS" << std::string(matrix->width() * 2 - 4, '_') << "\n";
   for (unsigned y = 0; y < matrix->height(); y++)
   {
      std::cout << "|";
      for (unsigned x = 0; x < matrix->width(); x++)
      {
         sharedConstPixel pixel = matrix->pixelAtPosition(x, y);

         char c;
         if (pixel->isUnitsEmpty())
         {
            c = '.';
         }
         else
         {
            c = 48 + pixel->nOfUnits();
         }
         std::cout << " " << c;
      }
      std::cout << "|\n";
   }
   std::cout << std::string(matrix->width() * 2 + 2, '^') << std::endl;
}
