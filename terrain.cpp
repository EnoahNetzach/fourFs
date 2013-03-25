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
   : m_matrix(width, height)
{
   int f = frequency;
   int p = int(pace);

   unsigned epochs = m_matrix.size() * range;
   boost::random::uniform_int_distribution<> intDist(1, f);
   boost::random::uniform_real_distribution<> realDist(- amplitude, amplitude);

   int x = m_matrix.width() / 2;
   int y = m_matrix.height() / 2;
   for (unsigned i = 0; i < epochs; ++i)
   {
      m_matrix.pixelAtPosition(x, y).height() += realDist(rng);

      unsigned num = intDist(rng);
      switch (num)
      {
      case 1:
         x = std::min(int(m_matrix.width()) - 1, x + p);
         break;
      case 2:
         x = std::max(0, x - p);
         break;
      case 3:
         y = std::min(int(m_matrix.height()) - 1, y + p);
         break;
      case 4:
         y = std::max(0, y - p);
         break;
      case 5:
         x = std::min(int(m_matrix.width()) - 1, x + p);
         y = std::min(int(m_matrix.height()) - 1, y + p);
         break;
      case 6:
         x = std::min(int(m_matrix.width()) - 1, x + p);
         y = std::max(0, y - p);
         break;
      case 7:
         x = std::max(0, x - p);
         y = std::min(int(m_matrix.height()) - 1, y + p);
         break;
      case 8:
         x = std::max(0, x - p);
         y = std::max(0, y - p);
         break;
      default:
         pixelsList pixelSquare = m_matrix.pixelsAroundPosition(x, y, square);
         BOOST_FOREACH(Pixel * pixel, pixelSquare)
         {
            pixel->height() += realDist(rng);
         }
         break;
      }
   }
   std::cout << "Before smoothing:\n" << std::flush;
   show();
   for (unsigned i = 0; i < m_matrix.size(); ++i)
   {
      Pixel & pixel = m_matrix.pixelAtIndex(i);

      double height = 0;

      pixelsList pixelSquare = m_matrix.pixelsAroundIndex(i, smooth);
      BOOST_FOREACH(const Pixel * p, pixelSquare)
      {
         height += p->height();
      }
      pixel.height() = height / pixelSquare.size();

      if (pixel.height() < 0) pixel.height() = 0;
      if (pixel.height() > 1) pixel.height() = 1;
   }
   std::cout << "After smoothing:\n" << std::flush;
   show();
}

Terrain::~Terrain()
{
}

unsigned Terrain::height() const
{
   return m_matrix.height();
}

unsigned Terrain::width() const
{
   return m_matrix.width();
}

Matrix & Terrain::matrix()
{
   return m_matrix;
}

const Matrix & Terrain::matrix() const
{
   return m_matrix;
}

void Terrain::show() const
{
   /*for (unsigned y = 0; y < m_matrix.height(); y++)
   {
      for (unsigned x = 0; x < m_matrix.width(); x++)
      {
         const Pixel & pixel = m_matrix.pixelAtPosition(x, y);

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

   std::cout << std::string(m_matrix.width(), '=') << "\n" << std::endl;*/

   for (unsigned y = 0; y < m_matrix.height(); y++)
   {
      for (unsigned x = 0; x < m_matrix.width(); x++)
      {
         const Pixel & pixel = m_matrix.pixelAtPosition(x, y);

         char c;
         if (pixel.height() < 0.1)
         {
            c = ' ';
         }
         else if (pixel.height() < 0.2)
         {
            c = '.';
         }
         else if (pixel.height() < 0.3)
         {
            c = '*';
         }
         else if (pixel.height() < 0.4)
         {
            c = ':';
         }
         else if (pixel.height() < 0.5)
         {
            c = 'o';
         }
         else if (pixel.height() < 0.6)
         {
            c = 'g';
         }
         else if (pixel.height() < 0.7)
         {
            c = '&';
         }
         else if (pixel.height() < 0.8)
         {
            c = '8';
         }
         else if (pixel.height() < 0.9)
         {
            c = '#';
         }
         else
         {
            c = '@';
         }
         std::cout << c << " ";
      }
      std::cout << "\n";
   }
   std::cout << std::endl;
}
