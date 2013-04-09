/*
 * openglinterface.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 *
 *  LIBS := -lGL -lGLU -lGLEW -lglfw
 *  This works only with OpenGl 3.3 or above

 */

#include "openglinterface.h"

#include <iostream>

#include "../Logic/map.h"
#include "../Logic/pixel.h"

using namespace fourFs;
using namespace logic;
using namespace view;

OpenGLInterface::OpenGLInterface(bool time)
   : Interface_base(time, "openGL")
{
   window_width = 1024;
   window_height = 768;
}

void OpenGLInterface::showImpl(logic::sharedConstMatrix matrix)
{

}

OpenGLInterface::~OpenGLInterface()
{
}

void OpenGLInterface::initializeImpl()
{
   bool windowError = initializeWindow();

   m_good = windowError;

}

void OpenGLInterface::showMapImpl(const logic::Map & map) const
{

   //SET VBO

   //SET SHADERS

   OpenGlMainLoop();

}

void OpenGLInterface::showUnitsImpl(const logic::Map & map) const
{
   std::cout << "An openGL fabulous show here!" << std::endl;
}

void OpenGLInterface::OpenGlMainLoop(void) const
{
   unsigned frameCount = 0;
   double oldTime = 0.;

   do
      {
         // Clear the screen
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         //DO SOMETHING

         ++frameCount;
         oldTime = fotogramsPerSecond(frameCount, 1.0, oldTime);     //FPS counter

         glfwSwapBuffers();   // Swap buffers

      }  while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));

      // Close OpenGL window and terminate GLFW
      glfwTerminate();
}

bool OpenGLInterface::initializeWindow(void)
{
   // Initialize GLFW
   if(!glfwInit())
   {
       std::cerr<<"Failed to initialize GLFW"<<std::endl;
       return false;
   }

   glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);                   // 4x antialiasing
   glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);           // Major number of the desired minimum OpenGL version.
   glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);           // Minor number of the desired minimum OpenGL version.
   glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    // Disallow legacy functionality if needed (OpenGl 3.0 or above)
   glfwOpenWindowHint(GLFW_OPENGL_PROFILE, 0);                 // Default. Let the system choose which context should implement.

   // Open a window "1024x768" and create its OpenGL context
   if(!glfwOpenWindow(window_width, window_height, 0,0,0,0, 32,0, GLFW_WINDOW))
   {
       std::cerr<<"Failed to open GLFW window"<<std::endl;

       glfwTerminate();

       return -1;
   }
       else
   {
       int major, minor, rev;

       glfwGetGLVersion(&major, &minor, &rev);

       std::cout<<"OpenGL version received: "<<major<<"."<<minor<<"."<<rev<<"\n"<<std::endl;
   }

   // Initialize GLEW
   glewExperimental = true; // Needed for core profile

   if (glewInit() != GLEW_OK) {

       std::cerr<<"Failed to initialize GLEW"<<std::endl;

       return false;
   }

   glfwSetWindowTitle(WINDOW_TITLE_DEFAULT); // Set a default Title

   // Black background -> Red-Green-Blue-Alpha
   glClearColor(0.0, 0.0, 0.0, 0.0);

   // Ensure we can capture the escape key being pressed below
   glfwEnable(GLFW_STICKY_KEYS);

   //END GLEW initialization

   return true;
}

double fotogramsPerSecond(unsigned int &frameCount, double step, double oldTime){

   double newTime = glfwGetTime();

   if(frameCount == 0){
      glfwSetTime(0.0);
   }

   if(std::abs(oldTime - newTime) > step)
   {
      unsigned int fps = frameCount/(newTime - oldTime);

      std::stringstream oss;

      oss << WINDOW_TITLE_DEFAULT <<" @"<< fps << " fps";

      std::string newTitle (oss.str());

      glfwSetWindowTitle(newTitle.c_str());

      oldTime = newTime;
      frameCount=0;
   }

   return oldTime;
}
