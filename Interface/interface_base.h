/*
 * interface_base.h
 *
 *  Created on: Apr 4, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_INTERFACE_BASE_H_
#define fourFs_INTERFACE_BASE_H_

#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/signals2.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/utility.hpp>

#include "../utilities.hpp"

namespace fourFs {
namespace interfaces {

class Interface_base : boost::noncopyable
{
public:
   typedef boost::signals2::signal< void() >  showSignal_type;
   typedef boost::signals2::connection connection_type;

   void run();
   void stop();
   void interrupt();
   void join();
   void connect(sharedInterface interface);
   void showMap() const;
   void showUnits() const;

protected:
   Interface_base(const char * name, logic::Simulation & simulation);
   virtual ~Interface_base();

   virtual void runImpl() = 0;

   void callShowMap() const;
   virtual void showMapImpl(logic::sharedConstMatrix matrix) const = 0;
   void callShowUnits() const;
   virtual void showUnitsImpl(logic::sharedConstMatrix matrix) const = 0;

   logic::Simulation & m_simulation;
   boost::mutex m_runMutex;

private:
   connection_type connectShowMap(const showSignal_type::slot_type & slot);
   connection_type connectShowUnits(const showSignal_type::slot_type & slot);

   const std::string m_name;
   boost::thread m_runThread;
   showSignal_type m_showMapSignal;
   std::list< connection_type > m_showMapConnections;
   showSignal_type m_showUnitsSignal;
   std::list< connection_type > m_showUnitsConnections;
};

} /* namespace interface */
} /* namespace fourFs */

#endif /* fourFs_INTERFACE_BASE_H_ */
