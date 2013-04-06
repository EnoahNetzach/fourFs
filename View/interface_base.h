/*
 * interface_base.h
 *
 *  Created on: Apr 4, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_INTERFACE_BASE_H_
#define fourFs_INTERFACE_BASE_H_

#include <boost/utility.hpp>

#include "../utilities.hpp"

namespace fourFs {
namespace view {

class Interface_base : boost::noncopyable
{
public:
   void initialize();
   virtual bool good() const;
   void showMap(const logic::Map & map) const;
   void showUnits(const logic::Map & map) const;

protected:
   Interface_base(bool time, const char * name);
   virtual ~Interface_base();

   virtual void initializeImpl() = 0;
   virtual void showMapImpl(const logic::Map & map) const = 0;
   virtual void showUnitsImpl(const logic::Map & map) const = 0;

   bool m_good;
   const char * m_name;

private:
   bool m_time;
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_INTERFACE_BASE_H_ */
