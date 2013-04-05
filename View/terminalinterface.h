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
   SINGLETON_DEF(TerminalInterface, protected)

public:
   void initialize();
   bool good() const;
   void showMap(const logic::Map & map) const;
   void showUnits(const logic::Map & map) const;

protected:

private:
};

} /* namespace view */
} /* namespace fourFs */
#endif /* fourFs_TERMINAL_H_ */
