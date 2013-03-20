/*
 * unit.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include "unit.h"

#include "state.h"

using namespace FourFs;

Unit::Unit(State & linkedState)
   : m_linkedState(& linkedState)
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

const State & Unit::linkedState() const
{
   return * m_linkedState;
}
