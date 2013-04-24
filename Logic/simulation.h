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
   friend class analysis::serialization::SerializeSimulation;

public:
   Simulation();
   Simulation(const Simulation & simulation);
   ~Simulation();

   void operator =(const Simulation & simulation);
   bool good() const;
   bool isRunning() const;
   bool isPaused() const;
   bool isStopped() const;
   unsigned & width();
   const unsigned & width() const;
   unsigned & height();
   const unsigned & height() const;
   double & range();
   const double & range() const;
   unsigned & frequency();
   const unsigned & frequency() const;
   double & amplitude();
   const double & amplitude() const;
   unsigned & pace();
   const unsigned & pace() const;
   unsigned & square();
   const unsigned & square() const;
   unsigned & smooth();
   const unsigned & smooth() const;
   sharedMap map();
   sharedConstMap map() const;
   unitList units();
   constUnitList units() const;
   void options(unsigned width, unsigned height, double range,
                unsigned frequency, double amplitude, unsigned pace,
                unsigned square, unsigned smooth);
   void newMap();
   void newMap(unsigned width, unsigned height, double range,
               unsigned frequency, double amplitude, unsigned pace,
               unsigned square, unsigned smooth);
   void addUnits(unsigned num);
   void deleteUnits(unsigned num = 0);
   void resizeUnits(unsigned num);
   void start();
   void pause();
   void resume();
   void stop();

protected:

private:
   void runLoop(); //god function

   unsigned m_width;
   unsigned m_height;
   double m_range;
   unsigned m_frequency;
   double m_amplitude;
   unsigned m_pace;
   unsigned m_square;
   unsigned m_smooth;
   sharedMap m_map;
   unitList m_units;
   boost::mutex m_mutex;
   boost::thread m_loopThread;
   bool m_isRunning;
   boost::condition_variable m_cond;
   bool m_shouldRun;
};

} /* namespace logic */
} /* namespace fourFs */

#endif /* fourFs_SIMULATION_H_ */
