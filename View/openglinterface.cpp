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

OpenGLInterface::OpenGLInterface(bool time)
   : Interface_base(time, "openGL")
{
}

OpenGLInterface::~OpenGLInterface()
{
}

void OpenGLInterface::initializeImpl()
{
   m_good = true;
}

void OpenGLInterface::showMapImpl(const logic::Map & map) const
{
   std::cout << "An openGL fabulous show here!" << std::endl;
}

void OpenGLInterface::showUnitsImpl(const logic::Map & map) const
{
   std::cout << "An openGL fabulous show here!" << std::endl;
}

//Devin sei bellissima (test)
