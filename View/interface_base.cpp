/*
 * interface_base.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: Enoah Netzach
 */

#include "interface_base.h"

#include "../Logic/map.h"

using namespace fourFs;
using namespace logic;
using namespace view;

Interface_base::Interface_base()
   : m_good(false)
{
}

Interface_base::~Interface_base()
{
}

void Interface_base::initialize()
{
}

bool Interface_base::good() const
{
   return m_good;
}

void Interface_base::showMap(const logic::Map & map) const
{
}

void Interface_base::showUnits(const logic::Map & map) const
{
}
