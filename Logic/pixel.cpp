/*
 * pixel.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "pixel.h"

#include <iostream>

#include "environment.h"
#include "unit.h"

using namespace fourFs;
using namespace logic;

Pixel::Pixel(unsigned index, bool border)
   : m_index(index)
   , m_height(0)
   , m_border(border)
{
}

Pixel::~Pixel()
{
}

unsigned Pixel::index () const
{
   return m_index;
}

double & Pixel::height()
{
   return m_height;
}

const double & Pixel::height() const
{
   return m_height;
}

bool Pixel::isBorder() const
{
   return m_border;
}

sharedEnvironment Pixel::environment()
{
   return m_environment;
}

sharedConstEnvironment Pixel::environment() const
{
   return m_environment;
}

bool Pixel::isUnitsEmpty() const
{
   return m_units.empty();
}

bool Pixel::isUnitsUnique() const
{
   return m_units.size() <= 1;
}

unsigned Pixel::nOfUnits() const
{
   return m_units.size();
}

void Pixel::addUnit(sharedUnit unit)
{
   m_units.push_back(unit);
}

bool Pixel::removeUnit(sharedConstUnit unit)
{
   bool found = false;
   unitIterator it;

   for (it = m_units.begin(); it != m_units.end(); ++it)
   {
      if ((* it) == unit)
      {
         found = true;
         m_units.erase(it);
         break;
      }
   }

   return found;
}

void Pixel::clearUnits()
{
   m_units.clear();
}

unitList & Pixel::units()
{
   return m_units;
}
