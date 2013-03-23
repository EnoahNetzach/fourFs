/*
 * state.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_STATE_H_
#define fourFs_STATE_H_

#include "utilities.hpp"

namespace FourFs
{

class State
{
public:
   explicit State();
   ~State();

   void addUnit(Unit & unit);
   bool removeUnit(const Unit & unit);
   void clearUnits();
   unitsList & units();

protected:

private:
   unitsList m_units;
};

} /* namespace FourFs */

#endif /* fourFs_STATE_H_ */
