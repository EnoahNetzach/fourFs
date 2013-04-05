/*
 * state.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_STATE_H_
#define fourFs_STATE_H_

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class State
{
public:
   explicit State();
   ~State();

   void addUnit(sharedUnit unit);
   bool removeUnit(sharedConstUnit unit);
   void clearUnits();
   unitList & units();

protected:

private:
   unitList m_units;
};

} /* namespace logic */
} /* namespace FourFs */

#endif /* fourFs_STATE_H_ */
