/*
 * openglinterface.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#include "openglinterface.h"

#include <iostream>

using namespace fourFs;
using namespace logic;
using namespace view;

SINGLETON_DEC(OpenGLInterface)

OpenGLInterface::OpenGLInterface()
{
}

OpenGLInterface::~OpenGLInterface()
{
}

void OpenGLInterface::initialize()
{
   m_good = true;
}

bool OpenGLInterface::good() const
{
   return m_good;
}

void OpenGLInterface::showMap(const logic::Map & map) const
{
   std::cout << "An openGL fabulous show here!" << std::endl;
}

void OpenGLInterface::showUnits(const logic::Map & map) const
{
   std::cout << "An openGL fabulous show here!" << std::endl;
}
