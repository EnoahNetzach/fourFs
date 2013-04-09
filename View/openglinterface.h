/*
 * openglinterface.h
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_OPENGLINTERFACE_H_
#define fourFs_OPENGLINTERFACE_H_

#include "interface_base.h"
#include "../utilities.hpp"

#include <GL/glew.h>          // Include GLEW
#include <GL/glfw.h>          // Include GLFW
#include <glm/glm.hpp>        // Include GLM

#include <sstream>
#include <math.h>

namespace fourFs {
namespace view {

#define WINDOW_TITLE_DEFAULT "Rob Halford?"

class OpenGLInterface : virtual public Interface_base
{
public:
   OpenGLInterface(bool time);
   ~OpenGLInterface();

protected:
   unsigned int window_width, window_height;

   void initializeImpl();
   bool initializeWindow();
   void showImpl(logic::sharedConstMatrix matrix);
   void showMapImpl(const logic::Map & map) const;
   void showUnitsImpl(const logic::Map & map) const;
   void OpenGlMainLoop(void) const;

private:
};

} /* namespace view */
} /* namespace fourFs */

double fotogramsPerSecond(unsigned int &, double, double);

#endif /* fourFs_OPENGLINTERFACE_H_ */
