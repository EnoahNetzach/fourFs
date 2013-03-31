/*
 * terrain.cpp
 *
 *  Created on: Mar 23, 2013
 *      Author: Enoah Netzach
 */

#include "terrain.h"
#include "pixel.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/random.hpp>

using namespace FourFs;

/*
 * range ~2.5
 *
 * frequency 10
 *
 * amplitude ~0.3
 *
 * pace 4
 *
 * square 4
 *
 * smooth 3
 */
Terrain::Terrain(unsigned width, unsigned height, double range,
                 unsigned frequency, double amplitude, unsigned pace,
                 unsigned square, unsigned smooth)
   : m_matrix(new Matrix(width, height))
{
   int f = frequency;
   int p = int(pace);

   unsigned epochs = m_matrix.get()->size() * range;
   boost::random::uniform_int_distribution<> intDist(1, f);
   boost::random::uniform_real_distribution<> realDist(- amplitude, amplitude);

   int x = m_matrix.get()->width() / 2;
   int y = m_matrix.get()->height() / 2;
   for (unsigned i = 0; i < epochs; ++i)
   {
      m_matrix.get()->pixelAtPosition(x, y).get()->height() += realDist(rng);

      unsigned num = intDist(rng);
      switch (num)
      {
      case 1:
         x = std::min(int(m_matrix.get()->width()) - 1, x + p);
         break;
      case 2:
         x = std::max(0, x - p);
         break;
      case 3:
         y = std::min(int(m_matrix.get()->height()) - 1, y + p);
         break;
      case 4:
         y = std::max(0, y - p);
         break;
      case 5:
         x = std::min(int(m_matrix.get()->width()) - 1, x + p);
         y = std::min(int(m_matrix.get()->height()) - 1, y + p);
         break;
      case 6:
         x = std::min(int(m_matrix.get()->width()) - 1, x + p);
         y = std::max(0, y - p);
         break;
      case 7:
         x = std::max(0, x - p);
         y = std::min(int(m_matrix.get()->height()) - 1, y + p);
         break;
      case 8:
         x = std::max(0, x - p);
         y = std::max(0, y - p);
         break;
      default:
         pixelsList pixelSquare = m_matrix.get()->pixelsAroundPosition(x, y, square);
         BOOST_FOREACH(sharedPixel pixel, pixelSquare)
         {
            pixel.get()->height() += realDist(rng);
         }
         break;
      }
   }
   std::cout << "Before smoothing:\n" << std::flush;
   show();
   for (unsigned i = 0; i < m_matrix.get()->size(); ++i)
   {
      sharedPixel pixel = m_matrix.get()->pixelAtIndex(i);

      double height = 0;

      pixelsList pixelSquare = m_matrix.get()->pixelsAroundIndex(i, smooth);
      BOOST_FOREACH(sharedConstPixel p, pixelSquare)
      {
         height += p.get()->height();
      }
      pixel.get()->height() = height / pixelSquare.size();

      if (pixel.get()->height() < 0) pixel.get()->height() = 0;
      if (pixel.get()->height() > 1) pixel.get()->height() = 1;
   }
   std::cout << "After smoothing:\n" << std::flush;
   show();
}

Terrain::~Terrain()
{
}

unsigned Terrain::height() const
{
   return m_matrix.get()->height();
}

unsigned Terrain::width() const
{
   return m_matrix.get()->width();
}

sharedMatrix Terrain::matrix()
{
   return m_matrix;
}

sharedConstMatrix Terrain::matrix() const
{
   return m_matrix;
}

void Terrain::show() const
{
   /*for (unsigned y = 0; y < m_matrix.get()->height(); y++)
   {
      for (unsigned x = 0; x < m_matrix.get()->width(); x++)
      {
         const Pixel & pixel = m_matrix.get()->pixelAtPosition(x, y);

         char c;
         if (pixel.isUnitsEmpty())
         {
            c = 'á';
         }
         else
         {
            c = 48 + pixel.nOfUnits();
         }
         std::cout << c << " ";
      }
      std::cout << "\n";
   }
   std::cout << std::endl;

   std::cout << std::string(m_matrix.get()->width(), '=') << "\n" << std::endl;*/

   for (unsigned y = 0; y < m_matrix.get()->height(); y++)
   {
      for (unsigned x = 0; x < m_matrix.get()->width(); x++)
      {
         sharedConstPixel pixel = m_matrix.get()->pixelAtPosition(x, y);

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
      std::cout << "\n";
   }
   std::cout << std::endl;
}
