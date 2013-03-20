/*
 * unit.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "unit.h"

using namespace FourFs;

Unit::Unit()
{
   // TODO Auto-generated constructor stub

}

Unit::~Unit()
{
   // TODO Auto-generated destructor stub
}

const unsigned & Unit::longevity () const
{
   return m_longevity;
}

const unsigned & Unit::fertility () const
{
   return m_fertility;
}

const unsigned & Unit::belligerance () const
{
   return m_belligerance;
}
