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

namespace fourFs {
namespace view {

class OpenGLInterface : virtual public Interface_base
{
public:
   OpenGLInterface(bool time);
   ~OpenGLInterface();

protected:
   void initializeImpl();
   void showMapImpl(const logic::Map & map) const;
   void showUnitsImpl(const logic::Map & map) const;

private:
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_OPENGLINTERFACE_H_ */
