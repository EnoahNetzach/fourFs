/*
 * terminal.h
 *
 *  Created on: Apr 5, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_TERMINAL_H_
#define fourFs_TERMINAL_H_

#include "../utilities.hpp"
#include "interface_base.h"

namespace fourFs
{
namespace view
{

class Terminal: virtual public fourFs::view::Interface_base
{
public:
   Terminal();
   ~Terminal();

   void initialize();
   bool good() const;
   void showMap(const logic::Map & map) const;
   void showUnits(const logic::Map & map) const;
};

} /* namespace view */
} /* namespace fourFs */
#endif /* fourFs_TERMINAL_H_ */
