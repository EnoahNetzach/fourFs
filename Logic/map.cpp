/*
 * terrain.cpp
 *
 *  Created on: Mar 23, 2013
 *      Author: Enoah Netzach
 */

#include "map.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/random.hpp>
#include <boost/timer/timer.hpp>

#include "pixel.h"

using namespace fourFs;
using namespace logic;

Map::Map()
   : m_matrix(new Matrix(0, 0))
{
}

Map::Map(unsigned width, unsigned height, double range,
                 unsigned frequency, double amplitude, unsigned pace,
                 unsigned square, unsigned smooth)
   : m_matrix(new Matrix(width, height))
{
   boost::timer::cpu_timer timer;
   if (Logger::verbose()) timer.start();

   int f = frequency;
   int p = int(pace);

   unsigned epochs = m_matrix->size() * range;
   boost::random::uniform_int_distribution<> intDist(1, f);
   boost::random::uniform_real_distribution<> realDist(- amplitude, amplitude);

   int x = m_matrix->width() / 2;
   int y = m_matrix->height() / 2;
   for (unsigned i = 0; i < epochs; ++i)
   {
      m_matrix->pixelAtPosition(x, y)->height() += realDist(rng);

      unsigned num = intDist(rng);
      switch (num)
      {
      case 1:
         x = std::min(int(m_matrix->width()) - 1, x + p);
         break;
      case 2:
         x = std::max(0, x - p);
         break;
      case 3:
         y = std::min(int(m_matrix->height()) - 1, y + p);
         break;
      case 4:
         y = std::max(0, y - p);
         break;
      case 5:
         x = std::min(int(m_matrix->width()) - 1, x + p);
         y = std::min(int(m_matrix->height()) - 1, y + p);
         break;
      case 6:
         x = std::min(int(m_matrix->width()) - 1, x + p);
         y = std::max(0, y - p);
         break;
      case 7:
         x = std::max(0, x - p);
         y = std::min(int(m_matrix->height()) - 1, y + p);
         break;
      case 8:
         x = std::max(0, x - p);
         y = std::max(0, y - p);
         break;
      default:
         pixelsList pixelSquare = m_matrix->pixelsAroundPosition(x, y, square);
         BOOST_FOREACH(sharedPixel pixel, pixelSquare)
         {
            pixel->height() += realDist(rng);
         }
         break;
      }
   }

   for (unsigned i = 0; i < m_matrix->size(); ++i)
   {
      sharedPixel pixel = m_matrix->pixelAtIndex(i);

      double height = 0;

      pixelsList pixelSquare = m_matrix->pixelsAroundIndex(i, smooth);
      BOOST_FOREACH(sharedConstPixel p, pixelSquare)
      {
         height += p->height();
      }
      pixel->height() = height / pixelSquare.size();

      if (pixel->height() < 0) pixel->height() = 0;
      if (pixel->height() > 1) pixel->height() = 1;
   }

   if (Logger::verbose())
   {
      timer.stop();
      Logger() << timer.format(boost::timer::default_places, timerFormat("Map generation")) << "\n";
   }
}

Map::~Map()
{
}

unsigned Map::height() const
{
   return m_matrix->height();
}

unsigned Map::width() const
{
   return m_matrix->width();
}

bool Map::empty() const
{
   return m_matrix->size() == 0;
}

sharedMatrix Map::matrix()
{
   return m_matrix;
}

sharedConstMatrix Map::matrix() const
{
   return m_matrix;
}
