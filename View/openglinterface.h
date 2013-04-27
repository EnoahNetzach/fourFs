/*
 * openglinterface.h
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_OPENGLINTERFACE_H_
#define fourFs_OPENGLINTERFACE_H_

#include <boost/thread.hpp>
#include <boost/random.hpp>

#include "../utilities.hpp"
#include "interface_base.h"

#include <GL/glew.h>          // Include GLEW
#include <GL/glfw.h>          // Include GLFW
#include <glm/glm.hpp>        // Include GLM
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

namespace fourFs {
namespace view {

#define WINDOW_TITLE_DEFAULT "Rob Halford?"

class OpenGLInterface : virtual public Interface_base
{
public:
   OpenGLInterface(bool time);
   ~OpenGLInterface();

protected:
   bool initialized, ENABLE_3D;
   unsigned window_width, window_height, numberOfBufferPoints, numberOfIndices, numberOfUnits;
   GLuint programID, frameCount;

   std::string windowTitleDefault;

   void cleanMesh(GLuint &, GLuint &, GLuint &, GLuint &, GLuint &, GLuint &, GLuint &);
   void computeMatricesFromInputs(glm::mat4 &, glm::mat4 &, glm::vec3 &, float &, float &);
   void drawMap(GLuint &, GLuint &, GLuint &);
   void drawUnits(GLuint &, GLuint &);
   void fotogramsPerSecond(double);
   void initializeImpl(void);
   void initializeShader(void);
   void loadMap(GLuint &, GLuint &, GLuint &, GLuint &, logic::sharedConstMatrix map, bool);
   void loadUnits(GLuint &, GLuint &, GLuint &, logic::sharedConstMatrix map, bool);
   void showImpl(logic::sharedConstMatrix map);

private:
   void runLoop(logic::sharedConstMatrix matrix, GLuint &, GLuint &, GLuint &, GLuint &, GLuint &, GLuint &, GLuint &);

   boost::thread m_runLoopThread;
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_OPENGLINTERFACE_H_ */
