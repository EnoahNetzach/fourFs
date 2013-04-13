/*
 * simulation.h
 *
 *  Created on: Apr 11, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_SIMULATION_H_
#define fourFs_SIMULATION_H_

#include <boost/thread.hpp>
#include <boost/utility.hpp>

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Simulation
{
public:
   Simulation();
   ~Simulation();

   bool good() const;
   sharedMap map();
   sharedConstMap map() const;
   unitList units();
   constUnitList units() const;
   void newMap(unsigned width, unsigned height, double range,
               unsigned frequency, double amplitude, unsigned pace,
               unsigned square, unsigned smooth);
   void addUnits(unsigned num);
   void deleteUnits(unsigned num = 0);
   void resizeUnits(unsigned num);
   void run();
   void pause();
   void resume();

protected:

private:
   void processData(); //god function

   sharedMap m_map;
   unitList m_units;
   boost::mutex m_mutex;
   boost::mutex m_loopMutex;
   boost::thread m_loopThread;
   boost::condition_variable m_cond;
   bool m_isComputing;

};

} /* namespace logic */
} /* namespace fourFs */

#endif /* fourFs_SIMULATION_H_ */
