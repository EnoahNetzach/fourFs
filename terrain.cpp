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

Terrain::Terrain(unsigned width, unsigned height)
   : m_matrix(width, height)
{
   /*
   boost::random::uniform_int_distribution<> indexDist(0, m_matrix.size() - 1);
   boost::random::uniform_real_distribution<> realDist1(0, 0.60);
   boost::random::uniform_real_distribution<> realDist2(- 0.25, 0.25);

   double indexes1 [m_matrix.size()];
   double indexes2 [m_matrix.size()];
   for (unsigned i = 0; i < m_matrix.size(); ++i)
   {
      indexes1[i] = i;
      indexes2[i] = i;
   }
   for (unsigned i = 0; i < m_matrix.size(); ++i)
   {
      unsigned index;
      double temp;

      index = indexDist(rng);
      temp = indexes1[i];
      indexes1[i] = indexes1[index];
      indexes1[index] = temp;

      index = indexDist(rng);
      temp = indexes2[i];
      indexes2[i] = indexes2[index];
      indexes2[index] = temp;
   }

   // generate the mesh
   for (unsigned i = 0; i < m_matrix.size(); ++i)
   {
      Pixel & pixel = m_matrix.pixelAtIndex(i);

      pixel.vivibility() = realDist1(rng);
   }
   double mean = 0;
   for (unsigned i = 0; i < m_matrix.size(); ++i)
   {
      Pixel & pixel = m_matrix.pixelAtIndex(indexes1[i]);

      pixel.vivibility() = 0;

      constPixelsList square = m_matrix.pixelsAroundIndex(indexes2[i], 1);
      BOOST_FOREACH(const Pixel * p, square)
      {
         pixel.vivibility() += p->vivibility();
      }
      pixel.vivibility() /= square.size();
      pixel.vivibility() += realDist2(rng);

      if (pixel.vivibility() < 0) pixel.vivibility() = 0;
      if (pixel.vivibility() > 1) pixel.vivibility() = 1;

      mean += pixel.vivibility();
   }
   std::cout << mean / m_matrix.size() << std::endl;
   /*/
   unsigned epochs = m_matrix.size() * 3;
   boost::random::uniform_int_distribution<> intDist(1, 10);
   boost::random::uniform_real_distribution<> realDist(- 0.25, 0.25);

   int x = m_matrix.width() / 2;
   int y = m_matrix.height() / 2;
   int pace = 2;
   for (unsigned i = 0; i < epochs; ++i)
   {
      m_matrix.pixelAtPosition(x, y).height() += realDist(rng);

      unsigned num = intDist(rng);
      switch (num)
      {
      case 1:
         x = std::min(int(m_matrix.width()) - 1, x + pace);
         break;
      case 2:
         x = std::max(0, x - pace);
         break;
      case 3:
         y = std::min(int(m_matrix.height()) - 1, y + pace);
         break;
      case 4:
         y = std::max(0, y - pace);
         break;
      case 5:
         x = std::min(int(m_matrix.width()) - 1, x + pace);
         y = std::min(int(m_matrix.height()) - 1, y + pace);
         break;
      case 6:
         x = std::min(int(m_matrix.width()) - 1, x + pace);
         y = std::max(0, y - pace);
         break;
      case 7:
         x = std::max(0, x - pace);
         y = std::min(int(m_matrix.height()) - 1, y + pace);
         break;
      case 8:
         x = std::max(0, x - pace);
         y = std::max(0, y - pace);
         break;
      default:
         pixelsList square = m_matrix.pixelsAroundPosition(x, y, 4);
         BOOST_FOREACH(Pixel * pixel, square)
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

      pixel.height() = 0;

      pixelsList square = m_matrix.pixelsAroundIndex(i, 3);
      BOOST_FOREACH(const Pixel * p, square)
      {
         pixel.height() += p->height();
      }
      pixel.height() /= square.size();

      if (pixel.height() < 0) pixel.height() = 0;
      if (pixel.height() > 1) pixel.height() = 1;
   }
   std::cout << "After smoothing:\n" << std::flush;
   show();
   //*/
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
