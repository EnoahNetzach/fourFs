/*
 * viewer.h
 *
 *  Created on: Apr 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_VIEWER_H_
#define fourFs_VIEWER_H_

#include "../utilities.hpp"

namespace fourFs {
namespace interfaces {

class Viewer
{
public:
   Viewer(logic::Simulation & simulation, Options op);
   ~Viewer();

   void run();
   void join();
   void stop();

protected:

private:
   interfaceList m_interfaces;
};

} /* namespace interfaces */
} /* namespace fourFs */
#endif /* fourFs_VIEWER_H_ */
