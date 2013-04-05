/*
 * interface_base.h
 *
 *  Created on: Apr 4, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_INTERFACE_BASE_H_
#define fourFs_INTERFACE_BASE_H_

#include "../utilities.hpp"

namespace fourFs {
namespace view {

class Interface_base
{
public:
   Interface_base();
   ~Interface_base();

   virtual void initialize();
   virtual bool good() const;
   virtual void showMap(const logic::Map & map) const;
   virtual void showUnits(const logic::Map & map) const;

protected:
   bool m_good;

private:
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_INTERFACE_BASE_H_ */
