/*
 * openglinterface.cpp
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#include <deque>

#include "openglinterface.h"
#include "../Logic/map.h"
#include "../Logic/pixel.h"
#include "load_shader.hpp"

using namespace fourFs;
using namespace logic;
using namespace view;

OpenGLInterface::OpenGLInterface(bool time)
   : Interface_base(time, "openGL")
{
   // initialization and other things NOT here
   // use initializeImpl() instead
   initialized = false;
   window_width = 1024, window_height = 768;
   numberOfBufferPoints = 0;
}

OpenGLInterface::~OpenGLInterface()
{
   // garbage collector, clear all

   // stops the run loop thread
   //m_runLoopThread.join();
}

void OpenGLInterface::initializeImpl()
{
   // resources init here!
   // if everything is OK set m_good to true, else set it to false.
   // If something more complex is needed, overload inherited bool good() const.
   // everything needed to show a new window here!

   if (initialized == false)
   {
      // Initialize GLFW
      if(!glfwInit())
      {
         std::cerr<<"Failed to initialize GLFW"<<std::endl;
         m_good = false;
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
         m_good = false;
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
         m_good = false;
      }

      glfwSetWindowTitle(WINDOW_TITLE_DEFAULT); // Set a Title

      // Black background -> Red-Green-Blue-Alpha
      glClearColor(0.0, 0.0, 0.0, 0.0);

      // Ensure we can capture the escape key being pressed below
      glfwEnable(GLFW_STICKY_KEYS);

      m_good = true;
      initialized = true;
   }


}

void OpenGLInterface::showImpl(sharedConstMatrix map)
{
   // everything needed to show a new window here!

   loadMap(vertexbuffer, colorbuffer, indexbuffer ,VertexArrayID, map);

   initializeShader();

   runLoop(vertexbuffer, colorbuffer, indexbuffer, VertexArrayID);

   //m_runLoopThread = boost::thread(& OpenGLInterface::runLoop, this);

}

void OpenGLInterface::initializeShader(void)
{
   // Create and compile our GLSL program from the shaders
   programID = LoadShaders( "View/VertexShader", "View/FragmentShader" );

   // Use our shader
   glUseProgram(programID);
}

void OpenGLInterface::runLoop(GLuint &vertexbuffer, GLuint &colorbuffer, GLuint &indexbuffer, GLuint &VertexArrayID)
{
   // the run loop!
   // Use boost mutex and boost interrupt points for code stability
   // (refer to http://www.boost.org/doc/libs/1_53_0/doc/html/thread.html).

   do
   {
      // Clear the screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

      // 1st attribute buffer: points
      glVertexAttribPointer(
         0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
         3,                  // size (X, Y, Z)
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,                  // stride
         (void*)0            // array buffer offset
      );

      glEnableVertexAttribArray(1);
      glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);

      // 2nd attribute buffer : colors
      glVertexAttribPointer(
         1,                                // attribute 1. No particular reason for 1, but must match the layout in the shader.
         3,                                // size
         GL_FLOAT,                         // type
         GL_FALSE,                         // normalized?
         0,                                // stride
         (void*)0                          // array buffer offset
      );

      // Index buffer
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

      // Draw the triangles !
      glDrawElements(
         GL_TRIANGLES,                // mode
         numberOfIndices,                  // count
         GL_UNSIGNED_INT,                  // type
         (void*)0                          // element array buffer offset
      );


      // Draw!!
      //glDrawArrays(GL_POINTS, 0, numberOfBufferPoints);

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);

      glfwSwapBuffers();   // Swap buffers

   }  while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));

   glDeleteBuffers(1, &vertexbuffer);
   glDeleteVertexArrays(1, &VertexArrayID);
   glDeleteProgram(programID);

   // Close OpenGL window and terminate GLFW
   glfwTerminate();

}


void OpenGLInterface::loadMap(GLuint &vertexbuffer, GLuint &colorbuffer, GLuint &indexbuffer, GLuint &VertexArrayID, logic::sharedConstMatrix matrix)
{
   glGenVertexArrays(1, &VertexArrayID);
   glBindVertexArray(VertexArrayID);

   // Generate 1 buffer, put the resulting identifier in vertexbuffer
   glGenBuffers(1, &vertexbuffer);

   std::vector<GLfloat> g_vertex_buffer_data;

   unsigned matrix_width = matrix->width(), matrix_height = matrix->height();

   for(unsigned x=0; x<(matrix_width); ++x)
   {
      for(unsigned y=0; y<matrix_height; ++y)
      {
         sharedConstPixel pixel = matrix->pixelAtPosition(x, y);

         float appo_x = ((float)x/matrix_width), appo_y = -((float)y/matrix_height);

         appo_x += -0.5;
         appo_y += 0.5;

         appo_x *= 2.05;
         appo_y *= 2.05;

         g_vertex_buffer_data.push_back(appo_x);
         g_vertex_buffer_data.push_back(appo_y);
         g_vertex_buffer_data.push_back( pixel->height() );

      }
   }

   numberOfBufferPoints = g_vertex_buffer_data.size();

   //DEBUG
   /*
   for(unsigned i=0, n=0; i<numberOfBufferPoints; ++i, ++n)
   {
      std::cout<<n<<") x: "<<g_vertex_buffer_data[i];
      ++i;
      std::cout<<" y: "<<g_vertex_buffer_data[i]<<"  ";
      ++i;
      std::cout<<" z: "<<g_vertex_buffer_data[i]<<std::endl;
   }
   */

   // The following commands will talk about our 'vertexbuffer' buffer
   glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
   glBufferData(GL_ARRAY_BUFFER, numberOfBufferPoints*sizeof(GLfloat), &g_vertex_buffer_data[0], GL_STATIC_DRAW);

   //INITIALIZE UVS

   std::vector<GLuint> g_index_buffer_data;

   for(unsigned x=0; x<matrix_width - 1 ; ++x)
   {
      for(unsigned y=0; y<matrix_height - 1; ++y)
      {
         g_index_buffer_data.push_back(y + (x*matrix_height));
         g_index_buffer_data.push_back(y+1 + (x*matrix_height));
         g_index_buffer_data.push_back(y+matrix_height + (x*matrix_height));

         g_index_buffer_data.push_back(y+matrix_height + (x*matrix_height));
         g_index_buffer_data.push_back(y+matrix_height+1 + (x*matrix_height));
         g_index_buffer_data.push_back(y+1 + (x*matrix_height));
      }
   }

   numberOfIndices = g_index_buffer_data.size();

   //DEBUG
   /*

   for(unsigned i=0, n=0; i<numberOfIndices; i+=3, ++n)
   {

      std::cout<<n<<") "<<g_index_buffer_data[i]<<" "<<g_index_buffer_data[i+1]<<" "<<g_index_buffer_data[i+2]<<std::endl;

   }
   */

   // Generate a buffer for the indices
   glGenBuffers(1, &indexbuffer);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(GLuint), &g_index_buffer_data[0] , GL_STATIC_DRAW);

   //INITIALIZE COLOR

   std::vector<GLfloat> g_color_buffer_data;

   for(unsigned i=0; i<numberOfBufferPoints; ++i)
   {
      float z_height = g_vertex_buffer_data[((i+1)*3)-1];

      if (z_height > 0.90)
      {
         g_color_buffer_data.push_back(z_height);
         g_color_buffer_data.push_back(z_height);
         g_color_buffer_data.push_back(z_height);

      }
      else if(z_height < 0.90 && z_height > 0.0)
      {
         g_color_buffer_data.push_back(0.);
         g_color_buffer_data.push_back(z_height+0.10); //std::max(1.-(z_height+0.10), 0.33) -> alternative
         g_color_buffer_data.push_back(0);
      }
      else
      {
         g_color_buffer_data.push_back(0.);
         g_color_buffer_data.push_back(0.);
         g_color_buffer_data.push_back(std::max(1. - std::abs(z_height), 0.15));
      }

   }

   //DEBUG
   /*
   for(unsigned i=0, n=0; i<numberOfBufferPoints; ++i, ++n)
   {
      std::cout<<n<<")  ( "<<g_color_buffer_data[i]<< " - ";
      ++i;
      std::cout<<g_color_buffer_data[i]<< " - ";
      ++i;
      std::cout<<g_color_buffer_data[i]<< " )"<<std::endl;
   }
   */

   // Generate 1 buffer, put the resulting identifier in colorbuffer
   glGenBuffers(1, &colorbuffer);

   // The following commands will talk about our 'colorbuffer' buffer
   glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
   glBufferData(GL_ARRAY_BUFFER, numberOfBufferPoints*sizeof(GLfloat), &g_color_buffer_data[0], GL_STATIC_DRAW);

}

