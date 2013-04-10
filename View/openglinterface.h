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

namespace fourFs {
namespace view {

class OpenGLInterface : virtual public Interface_base
{
public:
   OpenGLInterface();
   ~OpenGLInterface();

protected:
   void initializeImpl();
   void showImpl(logic::sharedConstMatrix map);

private:
   void runLoop();

   boost::thread m_runLoopThread;
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_OPENGLINTERFACE_H_ */
