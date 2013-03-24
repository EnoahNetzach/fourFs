/*
 * terrain.cpp
 *
 *  Created on: Mar 23, 2013
 *      Author: Enoah Netzach
 */

#include "terrain.h"
#include "pixel.h"

#include <iostream>

using namespace FourFs;

Terrain::Terrain(unsigned width, unsigned height)
   : m_matrix(width, height)
{
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
   for (unsigned y = 0; y < m_matrix.height(); y++)
   {
      for (unsigned x = 0; x < m_matrix.width(); x++)
      {
         const Pixel & pixel = m_matrix.pixelAtPosition(x, y);

         char c;
         if (pixel.isUnitsEmpty())
         {
            c = 183;
         }
         else
         {
            c = 48 + pixel.nOfUnits();
         }
         std::cout << c << " ";
      }
      std::cout << "\n";
   }
   std::cout << std::flush;
}
