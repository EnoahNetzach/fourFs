/*
 * terminal.h
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_TERMINALINTERFACE_H_
#define fourFs_TERMINALINTERFACE_H_

#include "../utilities.hpp"
#include "interface_base.h"

namespace fourFs {
namespace view {

class TerminalInterface: virtual public Interface_base
{
public:
   TerminalInterface(bool time);
   ~TerminalInterface();

protected:
   void initializeImpl();
   void showImpl(logic::sharedConstMatrix matrix);
   void showUnitsImpl(const logic::Map & map) const;

private:
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_TERMINAL_H_ */
