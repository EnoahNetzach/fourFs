/*
 * terrain.cpp
 *
 *  Created on: Mar 23, 2013
 *      Author: Enoah Netzach
 */

#include "map.h"
#include "pixel.h"

#include <algorithm>
#include <iostream>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/random.hpp>
#include <boost/timer/timer.hpp>

using namespace fourFs;
using namespace logic;

Map::Map(unsigned width, unsigned height, double range,
                 unsigned frequency, double amplitude, unsigned pace,
                 unsigned square, unsigned smooth, bool time)
   : m_matrix(new Matrix(width, height))
{
   boost::timer::cpu_timer timer;
   if (time) timer.start();

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

   if (time)
   {
      timer.stop();
      std::string format = "Map generation time:\n> %ws wall, %us user + %ss system = %ts CPU (%p%)";
      std::cout << timer.format(boost::timer::default_places, format) << std::endl;
   }
}

Map::~Map()
{
}

unsigned Map::height() const
{
   return m_matrix.get()->height();
}

unsigned Map::width() const
{
   return m_matrix.get()->width();
}

sharedMatrix Map::matrix()
{
   return m_matrix;
}

sharedConstMatrix Map::matrix() const
{
   return m_matrix;
}
