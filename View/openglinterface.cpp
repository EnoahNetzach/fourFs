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
   ENABLE_3D = false;
   window_width = 1024, window_height = 768;
   FoV = 45.;
   numberOfBufferPoints = 0;
}

OpenGLInterface::~OpenGLInterface()
{
   // garbage collector, clear all

   // stops the run loop thread
   //m_runLoopThread.join();
}

void OpenGLInterface::cleanMesh(GLuint &vertexBufferMap, GLuint &colorBufferMap, GLuint &indexBufferMap, GLuint &vertexArrayMapID, GLuint &vertexBufferUnits, GLuint &colorBufferUnits, GLuint &vertexUnitsID)
{
   glDeleteBuffers(1, &vertexBufferMap);
   glDeleteBuffers(1, &vertexBufferUnits);
   glDeleteBuffers(1, &colorBufferMap);
   glDeleteBuffers(1, &colorBufferUnits);
   glDeleteBuffers(1, &indexBufferMap);
   glDeleteVertexArrays(1, &vertexArrayMapID);
   glDeleteVertexArrays(1, &vertexUnitsID);
}

void OpenGLInterface::computeMatricesFromInputs(glm::mat4 &ProjectionMatrix, glm::mat4 &ViewMatrix, glm::vec3 &position, float &verticalAngle, float &horizontalAngle)
{
   static double lastTime = glfwGetTime();
   double currentTime = glfwGetTime();
   float deltaTime = float(currentTime - lastTime);

   double mouseWeel = glfwGetMouseWheel();      //int, float, long int doesn't work ???

   if((FoV - mouseWeel > 0.) && (FoV - mouseWeel < 180.)) FoV -= mouseWeel;
   else if(FoV > 180.) FoV = 180.;
   else if(FoV < 0.) FoV = 0.;

   glfwSetMouseWheel(0);

   enum keyboardKeys { key_A = 65, key_W = 87, key_D = 68, key_S = 83};

   if(glfwGetKey(key_A))
   {
      position[0] -= 0.6 * deltaTime;
   }
   if(glfwGetKey(key_D))
   {
      position[0] += 0.6 * deltaTime;
   }
   if(glfwGetKey(key_W))
   {
      position[1] += 0.6 * deltaTime;
   }
   if(glfwGetKey(key_S))
   {
      position[1] -= 0.6 * deltaTime;
   }
   if(glfwGetKey(GLFW_KEY_UP))
   {
      verticalAngle += 0.4 * deltaTime;
   }
   if(glfwGetKey(GLFW_KEY_DOWN))
   {
      verticalAngle -= 0.4 * deltaTime;
   }

   // Projection matrix : Field of View, ratio, display range : 0.1 unit <-> 100 units
   ProjectionMatrix = glm::perspective(FoV, (float)(window_width/window_height), (float)0.1, (float)100.0);
   // Camera matrix

   // Direction : Spherical coordinates to Cartesian coordinates conversion
   glm::vec3 direction(
           std::cos(verticalAngle) * std::sin(horizontalAngle),
           std::sin(verticalAngle),
           std::cos(verticalAngle) * std::cos(horizontalAngle)
   );

   // Right vector
   glm::vec3 right = glm::vec3(
           std::sin(horizontalAngle - 3.14/2.0),
           0,
           std::cos(horizontalAngle - 3.14/2.0)
   );

   // Up vector
   glm::vec3 up = glm::cross( right, direction );

   ViewMatrix = glm::lookAt
   (
         position,           // Camera is here
         position+direction, // and looks here : at the same position, plus "direction"
         up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

   // For the next frame, the "last time" will be "now"
   lastTime = currentTime;
}

void OpenGLInterface::drawMap(GLuint &vertexBufferMap, GLuint &colorBufferMap, GLuint &indexBufferMap)
{
   glBindBuffer(GL_ARRAY_BUFFER, vertexBufferMap);
   glEnableVertexAttribArray(0);

   // 1st attribute buffer: maps
   glVertexAttribPointer(
      0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      3,                  // size (X, Y, Z)
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
   );

   glBindBuffer(GL_ARRAY_BUFFER, colorBufferMap);
   glEnableVertexAttribArray(1);

   // 2nd attribute buffer : color_map
   glVertexAttribPointer(
      1,                                // attribute 1. No particular reason for 1, but must match the layout in the shader.
      3,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0                          // array buffer offset
   );

   // Index buffer
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferMap);

   // Draw the triangles !
   glDrawElements(
      GL_TRIANGLES,                     // mode
      numberOfIndices,                  // count
      GL_UNSIGNED_INT,                  // type
      (void*)0                          // element array buffer offset
   );
}

void OpenGLInterface::drawUnits(GLuint &vertexBufferUnits, GLuint &colorBufferUnits)
{
   glBindBuffer(GL_ARRAY_BUFFER, vertexBufferUnits);
   glEnableVertexAttribArray(0);

   // 1st attribute buffer: units
   glVertexAttribPointer(
      0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      3,                  // size (X, Y, Z)
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
   );

   glBindBuffer(GL_ARRAY_BUFFER, colorBufferUnits);
   glEnableVertexAttribArray(1);

   // 2nd attribute buffer : color_map
   glVertexAttribPointer(
      1,                                // attribute 1. No particular reason for 1, but must match the layout in the shader.
      3,                                // size
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0                          // array buffer offset
   );

   //Draw!!
   glDrawArrays(GL_POINTS, 0, numberOfUnits);
}

void OpenGLInterface::fotogramsPerSecond(double step)
{
   static double oldTime = glfwGetTime();
   static float frameCount = 0;
   double newTime = glfwGetTime();

   if(std::abs(oldTime - newTime) > step)
   {
      unsigned int fps = frameCount/(newTime - oldTime);

      std::stringstream oss;

      oss << WINDOW_TITLE_DEFAULT <<" @"<< fps << " fps";

      std::string newTitle (oss.str());

      glfwSetWindowTitle(newTitle.c_str());

      oldTime = newTime;
      frameCount = 0;
   }
   ++frameCount;
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

      // Lovely pink background -> Red-Green-Blue-Alpha
      glClearColor(1.0, 0.702, 0.855, 0.0);

      // Ensure we can capture the escape key being pressed below
      glfwEnable(GLFW_STICKY_KEYS);

      m_good = true;
      initialized = true;
   }


}

void OpenGLInterface::showImpl(sharedConstMatrix map)
{
   // everything needed to show a new window here!
   GLuint vertexBufferMap, colorBufferMap, indexBufferMap, vertexArrayMapID;

   loadMap(vertexBufferMap, colorBufferMap, indexBufferMap , vertexArrayMapID, map, ENABLE_3D);

   GLuint vertexBufferUnits, colorBufferUnits, vertexUnitsID;

   loadUnits(vertexBufferUnits, colorBufferUnits, vertexUnitsID, map, ENABLE_3D);

   initializeShader();

   runLoop(map, vertexBufferMap, colorBufferMap, indexBufferMap, vertexArrayMapID, vertexBufferUnits, colorBufferUnits, vertexUnitsID);

   //m_runLoopThread = boost::thread(& OpenGLInterface::runLoop, this);

}

void OpenGLInterface::initializeShader(void)
{
   // Create and compile our GLSL program from the shaders
   programID = LoadShaders( "View/VertexShader", "View/FragmentShader" );

   // Use our shader
   glUseProgram(programID);
}

void OpenGLInterface::loadMap(GLuint &vertexBufferMap, GLuint &colorBufferMap, GLuint &indexBufferMap, GLuint &vertexArrayMapID, logic::sharedConstMatrix matrix, bool ENABLED_3D)
{
   glGenVertexArrays(1, &vertexArrayMapID);
   glBindVertexArray(vertexArrayMapID);

   // Generate 1 buffer, put the resulting identifier in vertexBufferMap
   glGenBuffers(1, &vertexBufferMap);

   std::vector<GLfloat> g_vertex_buffer_data;
   std::vector<GLfloat> appo_vertex_z_data;

   unsigned matrix_width = matrix->width(), matrix_height = matrix->height();

   for(unsigned x=0; x<(matrix_width); ++x)
   {
      for(unsigned y=0; y<matrix_height; ++y)
      {
         sharedConstPixel pixel = matrix->pixelAtPosition(x, y);

         float appo_x = ((float)x/matrix_width), appo_y = -((float)y/matrix_height);

         appo_x += -0.5;
         appo_y += 0.5;

         appo_x *= 2.055;
         appo_y *= 2.055;

         g_vertex_buffer_data.push_back(appo_x);
         g_vertex_buffer_data.push_back(appo_y);
         appo_vertex_z_data.push_back(pixel->height());

         if(ENABLED_3D == true)
         {
            if(pixel->height()>=0)
            {
               g_vertex_buffer_data.push_back( pixel->height()/2 );
            }
            else g_vertex_buffer_data.push_back(0.0);
         }
         else g_vertex_buffer_data.push_back(0.0);
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

   for(unsigned i=0, n=0; i<numberOfBufferPoints; ++i, ++n)
   {
      if(g_vertex_buffer_data[i] > 1|| g_vertex_buffer_data[i+1] > 1 || g_vertex_buffer_data[i+2] > 1)
      {
         std::cout<<n<<") x: "<<g_vertex_buffer_data[i];
         ++i;
         std::cout<<" y: "<<g_vertex_buffer_data[i]<<"  ";
         ++i;
         std::cout<<" z: "<<g_vertex_buffer_data[i]<<std::endl;
      }
   }
*/

   // The following commands will talk about our 'vertexBufferMap' buffer
   glBindBuffer(GL_ARRAY_BUFFER, vertexBufferMap);
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
   glGenBuffers(1, &indexBufferMap);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferMap);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(GLuint), &g_index_buffer_data[0] , GL_STATIC_DRAW);

   //INITIALIZE COLOR

   std::vector<GLfloat> g_color_buffer_data;

   for(unsigned i=0; i<appo_vertex_z_data.size(); ++i)
   {
      float z_height = appo_vertex_z_data[i];

      if (z_height > 0.90)
      {
         g_color_buffer_data.push_back(z_height);
         g_color_buffer_data.push_back(z_height);
         g_color_buffer_data.push_back(z_height);

      }
      else if(z_height < 0.90 && z_height > 0.0)
      {
         g_color_buffer_data.push_back(0.);
         g_color_buffer_data.push_back(z_height+0.10);
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

   // Generate 1 buffer, put the resulting identifier in colorBufferMap
   glGenBuffers(1, &colorBufferMap);

   // The following commands will talk about our 'colorBufferMap' buffer
   glBindBuffer(GL_ARRAY_BUFFER, colorBufferMap);
   glBufferData(GL_ARRAY_BUFFER, numberOfBufferPoints*sizeof(GLfloat), &g_color_buffer_data[0], GL_STATIC_DRAW);
}

void OpenGLInterface::loadUnits(GLuint &vertexBufferUnits, GLuint &colorBufferUnits, GLuint &vertexUnitsID, logic::sharedConstMatrix matrix, bool ENABLED_3D)
{

   glGenVertexArrays(1, &vertexUnitsID);
   glBindVertexArray(vertexUnitsID);

   unsigned matrix_width = matrix->width(), matrix_height = matrix->height();
   std::vector<GLfloat> g_units_buffer_data;

      for(unsigned x=0; x<(matrix_width); ++x)
      {
         for(unsigned y=0; y<matrix_height; ++y)
         {
            sharedConstPixel pixel = matrix->pixelAtPosition(x, y);

            if(!(pixel->isUnitsEmpty()))
            {
               float appo_x = ((float)x/matrix_width), appo_y = -((float)y/matrix_height);

               appo_x += 0.5;
               appo_y += 0.5;

               appo_x *= 2.05;
               appo_y *= 2.05;

               g_units_buffer_data.push_back(appo_x);
               g_units_buffer_data.push_back(appo_y);

               if(ENABLED_3D == true)
               {
                  g_units_buffer_data.push_back( pixel->height());

               }
               else g_units_buffer_data.push_back(0.0);
            }
         }
      }

      numberOfUnits = g_units_buffer_data.size();

      //DEBUG
   /*
      for(unsigned i=0, n=0; i<numberOfUnits; ++i, ++n)
      {
         std::cout<<n<<") x: "<<g_units_buffer_data[i];
         ++i;
         std::cout<<" y: "<<g_units_buffer_data[i]<<"  ";
         ++i;
         std::cout<<" z: "<<g_units_buffer_data[i]<<std::endl;
      }
   */

      // Generate 1 buffer, put the resulting identifier in colorBufferMap
      glGenBuffers(1, &vertexBufferUnits);

      // The following commands will talk about our 'colorBufferMap' buffer
      glBindBuffer(GL_ARRAY_BUFFER, vertexBufferUnits);
      glBufferData(GL_ARRAY_BUFFER, numberOfUnits*sizeof(GLfloat), &g_units_buffer_data[0], GL_STATIC_DRAW);

      //COLORS:

      std::vector<GLfloat> g_units_color_data;

      for(unsigned i=0; i<numberOfUnits; ++i)
      {
         g_units_color_data.push_back(1.0);
         g_units_color_data.push_back(0.0);
         g_units_color_data.push_back(0.0);
      }

      // Generate 1 buffer, put the resulting identifier in colorBufferMap
      glGenBuffers(1, &colorBufferUnits);

      // The following commands will talk about our 'colorBufferMap' buffer
      glBindBuffer(GL_ARRAY_BUFFER, colorBufferUnits);
      glBufferData(GL_ARRAY_BUFFER, numberOfUnits*sizeof(GLfloat), &g_units_color_data[0], GL_STATIC_DRAW);
}

void OpenGLInterface::runLoop(logic::sharedConstMatrix map, GLuint &vertexBufferMap, GLuint &colorBufferMap, GLuint &indexBufferMap, GLuint &vertexArrayMapID, GLuint &vertexBufferUnits, GLuint &colorBufferUnits, GLuint &vertexUnitsID)
{
   // the run loop!
   // Use boost mutex and boost interrupt points for code stability
   // (refer to http://www.boost.org/doc/libs/1_53_0/doc/html/thread.html).

   double oldTimeEvents = 0;

   glfwSetTime(0.0);


   glm::mat4 ViewMatrix;
   glm::mat4 ProjectionMatrix;
   glm::vec3 position = glm::vec3(0, 0, 3.5);               // Initial position : on +Z
   float verticalAngle = 0.0, horizontalAngle = 3.1415;

   // Get a handle for our "MVP" uniform
   GLuint MatrixID = glGetUniformLocation(programID, "MVP");

   do
   {
      // Clear the screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


      // Enable depth test
      glEnable(GL_DEPTH_TEST);
      // Accept fragment if it closer to the camera than the former one
      glDepthFunc(GL_LESS);


      computeMatricesFromInputs(ProjectionMatrix, ViewMatrix, position, verticalAngle, horizontalAngle);

      if(glfwGetKey(90) && (std::abs(oldTimeEvents - glfwGetTime()) > 0.3))
      {
         (ENABLE_3D == true) ? ENABLE_3D = false : ENABLE_3D = true;

         cleanMesh(vertexBufferMap, colorBufferMap, indexBufferMap, vertexArrayMapID, vertexBufferUnits, colorBufferUnits, vertexUnitsID);

         loadMap(vertexBufferMap, colorBufferMap, indexBufferMap , vertexArrayMapID, map, ENABLE_3D);
         loadUnits(vertexBufferUnits, colorBufferUnits, vertexUnitsID, map, ENABLE_3D);

         oldTimeEvents = glfwGetTime();
      }

      glm::mat4 ModelMatrix = glm::mat4(1.0);

      glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

      // Send our transformation to the currently bound shader,
      // in the "MVP" uniform
      glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

      drawMap(vertexBufferMap, colorBufferMap, indexBufferMap);

      drawUnits(vertexBufferUnits, colorBufferUnits);

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);

      glfwSwapBuffers();   // Swap buffers

      fotogramsPerSecond(1.0);     //FPS counter

   }  while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));

   cleanMesh(vertexBufferMap, colorBufferMap, indexBufferMap, vertexArrayMapID, vertexBufferUnits, colorBufferUnits, vertexUnitsID);
   glDeleteProgram(programID);
   glfwTerminate();   // Close OpenGL window and terminate GLFW

}
