/*
 * terminal.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#include "terminalinterface.h"

#include <iostream>

#include <boost/lexical_cast.hpp>

#include "../Analysis/serialization.h"
#include "../logger.h"
#include "../Logic/map.h"
#include "../Logic/matrix.h"
#include "../Logic/pixel.h"
#include "../Logic/simulation.h"
#include "../Logic/unit.h"

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
      std::cout << "[Term interface] What would you like to do?\n"
                   "p=play/pause, r=resume, s=stop, y=reload script\n"
                   "m=new map, u=resize units, o=change options\n"
                   "v=save map, l=load map, w=show, i=info, q=quit\n> " << std::flush;
      input.clear();
      std::cin >> input;

      if (input == "p") // play/pause
      {
         if (m_simulation.isRunning())
         {
            m_simulation.pause();
         }
         else if (m_simulation.isPaused())
         {
            m_simulation.resume();
         }
         else
         {
            m_simulation.start();
         }
      }
      else if (input == "r") // resume
      {
         m_simulation.resume();
      }
      else if (input == "s") // stop
      {
         m_simulation.stop();
      }
      else if (input == "y") // reload script
      {
         m_simulation.reloadScript();
      }
      else if (input == "m") // new map
      {
         m_simulation.stop();
         std::cout << "[Term interface] New map with:"
                   << std::setprecision(7)
                   << std::setw(25) << std::left << "\nwidth = " << m_simulation.width()
                   << std::setw(25) << std::left << "\nheight = " << m_simulation.height()
                   << std::setw(25) << std::left << "\nrange = " << m_simulation.range()
                   << std::setw(25) << std::left << "\nfrequency" << m_simulation.frequency()
                   << std::setw(25) << std::left << "\namplitude = " << m_simulation.amplitude()
                   << std::setw(25) << std::left << "\npace" << m_simulation.pace()
                   << std::setw(25) << std::left << "\nsquare = " << m_simulation.square()
                   << std::setw(25) << std::left << "\nsmooth = " << m_simulation.smooth()
                   << std::endl;
         m_simulation.newMap();
      }
      else if (input == "u") // resize units
      {
         std::cout << "[Term interface] Resize units (now " << m_simulation.units().size()
                   << ") (c=cancel) " << std::flush;
         input.clear();
         std::cin >> input;

         if (input == "c") continue;
         m_simulation.resizeUnits(boost::lexical_cast< unsigned >(input));
      }
      else if (input == "o") // change options
      {
         std::cout << "[Term interface] What would you like to change\n"
                      "(w=width, h=height, l=length, r=range, f=frequency,\n"
                      "a=amplitude, p=pace, s=square, m=smooth, c=cancel)\n> " << std::flush;
         input.clear();
         std::cin >> input;

         if (input == "c") continue;
         else if (input == "w") // change options - width
         {
            std::cout << "[Term interface] Insert map width (now " << m_simulation.width()
                      << ") (c=cancel) " << std::flush;
            input.clear();
            std::cin >> input;

            if (input == "c") continue;
            m_simulation.width() = boost::lexical_cast< unsigned >(input);
         }
         else if (input == "h") // change options - height
         {
            std::cout << "[Term interface] Insert map height (now " << m_simulation.height()
                      << ") (c=cancel) " << std::flush;
            input.clear();
            std::cin >> input;

            if (input == "c") continue;
            m_simulation.height() = boost::lexical_cast< unsigned >(input);
         }
         else if (input == "l") // change options - length
         {
            std::cout << "[Term interface] Insert map length (now " << m_simulation.width()
                      << " x " << m_simulation.height() << ") (c=cancel) " << std::flush;
            input.clear();
            std::cin >> input;

            if (input == "c") continue;
            m_simulation.width() = boost::lexical_cast< unsigned >(input);
            m_simulation.height() = boost::lexical_cast< unsigned >(input);
         }
         else if (input == "r") // change options - range
         {
            std::cout << "[Term interface] Insert map range (now " << m_simulation.range()
                      << ") (c=cancel) " << std::flush;
            input.clear();
            std::cin >> input;

            if (input == "c") continue;
            m_simulation.range() = boost::lexical_cast< unsigned >(input);
         }
         else if (input == "f") // change options - frequency
         {
            std::cout << "[Term interface] Insert map frequency (now " << m_simulation.frequency()
                      << ") (c=cancel) " << std::flush;
            input.clear();
            std::cin >> input;

            if (input == "c") continue;
            m_simulation.frequency() = boost::lexical_cast< unsigned >(input);
         }
         else if (input == "a") // change options - amplitude
         {
            std::cout << "[Term interface] Insert map amplitude (now " << m_simulation.amplitude()
                      << ") (c=cancel) " << std::flush;
            input.clear();
            std::cin >> input;

            if (input == "c") continue;
            m_simulation.amplitude() = boost::lexical_cast< unsigned >(input);
         }
         else if (input == "p") // change options - pace
         {
            std::cout << "[Term interface] Insert map pace (now " << m_simulation.pace()
                      << ") (c=cancel) " << std::flush;
            input.clear();
            std::cin >> input;

            if (input == "c") continue;
            m_simulation.pace() = boost::lexical_cast< unsigned >(input);
         }
         else if (input == "s") // change options - square
         {
            std::cout << "[Term interface] Insert map square (now " << m_simulation.square()
                      << ") (c=cancel) " << std::flush;
            input.clear();
            std::cin >> input;

            if (input == "c") continue;
            m_simulation.square() = boost::lexical_cast< unsigned >(input);
         }
         else if (input == "m") // change options - smooth
         {
            std::cout << "[Term interface] Insert map smooth (now " << m_simulation.smooth()
                      << ") (c=cancel) " << std::flush;
            input.clear();
            std::cin >> input;

            if (input == "c") continue;
            m_simulation.smooth() = boost::lexical_cast< unsigned >(input);
         }
      }
      else if (input == "v") // save map
      {
         bool wasRunning = m_simulation.isRunning();
         m_simulation.pause();
         analysis::serialization::save(m_simulation);
         if (wasRunning) m_simulation.start();
      }
      else if (input == "l") // load map
      {
         m_simulation.stop();

         try
         {
            analysis::serialization::load(m_simulation);
         }
         catch (...)
         {
            std::cerr << "Some error occured while loading the map." << std::endl;
         }
      }
      else if (input == "w") // show
      {
         std::cout << "[Term interface] What would you like to show? (m=map, u=units, c=cancel) " << std::flush;
         input.clear();
         std::cin >> input;

         if (input == "c") continue;
         if (input == "m") callShowMap();
         if (input == "u") callShowUnits();
      }
      else if (input == "i") // info
      {
         std::cout << "[Term interface] Map with:"
                   << std::setprecision(7)
                   << std::setw(30) << std::left << "\nwidth = " << m_simulation.width()
                   << std::setw(30) << std::left << "\nheight = " << m_simulation.height()
                   << std::setw(30) << std::left << "\nrange = " << m_simulation.range()
                   << std::setw(30) << std::left << "\nfrequency" << m_simulation.frequency()
                   << std::setw(30) << std::left << "\namplitude = " << m_simulation.amplitude()
                   << std::setw(30) << std::left << "\npace" << m_simulation.pace()
                   << std::setw(30) << std::left << "\nsquare = " << m_simulation.square()
                   << std::setw(30) << std::left << "\nsmooth = " << m_simulation.smooth()
                   << std::setw(30) << std::left << "\nnumber of units = " << m_simulation.units().size()
                   << std::endl;
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
