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
   // initialization and other things NOT here
   // use initializeImpl() instead.
}

OpenGLInterface::~OpenGLInterface()
{
   // garbage collector, clear all

   // stops the run loop thread
   m_runLoopThread.join();
}

void OpenGLInterface::initializeImpl()
{
   // resources init here!
   // if everything is OK set m_good to true, else set it to false.
   // If something more complex is needed, overload inherited bool good() const.

   m_good = true;
}

void OpenGLInterface::showImpl(sharedConstMatrix map)
{
   // everything needed to show a new window here!

   m_runLoopThread = boost::thread(& OpenGLInterface::runLoop, this);
}

void OpenGLInterface::runLoop()
{
   // the run loop!
   // Use boost mutex and boost interrupt points for code stability
   // (refer to http://www.boost.org/doc/libs/1_53_0/doc/html/thread.html).

   while (true)
   {
      // ...
   }
}
