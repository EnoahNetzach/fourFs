/*
 * openglinterface.h
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_OPENGLINTERFACE_H_
#define fourFs_OPENGLINTERFACE_H_

#include <boost/thread.hpp>

#include "../utilities.hpp"
#include "interface_base.h"

#include <GL/glew.h>          // Include GLEW
#include <GL/glfw.h>          // Include GLFW

#include <iostream>
#include <fstream>

namespace fourFs {
namespace view {

#define WINDOW_TITLE_DEFAULT "Rob Halford?"
#define NUMBER_OF_TRIANGLES 100

class OpenGLInterface : virtual public Interface_base
{
public:
   OpenGLInterface(bool time);
   ~OpenGLInterface();

protected:
   bool initialized;
   unsigned window_width, window_height, numberOfBufferPoints;
   GLuint vertexbuffer, VertexArrayID, programID, colorbuffer;

   std::string windowTitleDefault;

   void initializeImpl();
   void showImpl(logic::sharedConstMatrix map);
   void loadMap(GLuint &, GLuint &, GLuint &, logic::sharedConstMatrix map);
   void initializeShader(void);

private:
   void runLoop(GLuint &, GLuint &, GLuint &);

   boost::thread m_runLoopThread;
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_OPENGLINTERFACE_H_ */
