/*
 * state.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_STATE_H_
#define fourFs_STATE_H_

#include <list>

namespace FourFs
{

class Unit;

class State
{
public:
   State();
   ~State();

protected:

private:
   std:list< Unit & > m_linkedUnits;
};

} /* namespace FourFs */

#endif /* fourFs_STATE_H_ */
