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

class OpenGLInterface : public Interface_base
{
public:
   OpenGLInterface();
   ~OpenGLInterface();
	
   void initialize();
   bool good() const;
   void showMap(const logic::Map & map) const;
   void showUnits(const logic::Map & map) const;

protected:

private:
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_OPENGLINTERFACE_H_ */
