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
   m_runLoopThread.interrupt();
}

void OpenGLInterface::initializeImpl()
{
   m_good = true;
}

void OpenGLInterface::showImpl(sharedConstMatrix map)
{
   std::cout << "An openGL fabulous show here!" << std::endl;

   m_runLoopThread = boost::thread(& OpenGLInterface::runLoop, this);
}

void OpenGLInterface::runLoop()
{
   while (true)
   {
      // ...
   }
}
