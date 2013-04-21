/*
 * terminal.h
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_TERMINALINTERFACE_H_
#define fourFs_TERMINALINTERFACE_H_

#include <boost/thread.hpp>

#include "../utilities.hpp"
#include "interface_base.h"

namespace fourFs {
namespace interfaces {

class TerminalInterface : public virtual Interface_base
{
public:
   TerminalInterface(logic::Simulation & simulation);

private:
   void runImpl();
   void showMapImpl(logic::sharedConstMatrix matrix) const;
   void showUnitsImpl(logic::sharedConstMatrix matrix) const;
};

} /* namespace interface */
} /* namespace fourFs */

#endif /* fourFs_TERMINAL_H_ */
