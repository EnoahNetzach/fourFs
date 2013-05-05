///*
// * terminal.h
// *
// *  Created on: Apr 5, 2013
// *      Author: Enoah Netzach
// */
//
//#ifndef fourFs_TERMINALINTERFACE_H_
//#define fourFs_TERMINALINTERFACE_H_
//
//#include <boost/thread.hpp>
//
//#include "../utilities.hpp"
//#include "interface_base.h"
//
//namespace fourFs {
//namespace view {
//
//class TerminalInterface: virtual public Interface_base
//{
//public:
//   TerminalInterface();
//   ~TerminalInterface();
//
//protected:
//   void initializeImpl();
//   void showImpl(logic::sharedConstMatrix matrix);
//   void runLoop();
//
//   logic::weakConstMatrix m_matrix;
//   boost::thread m_loopThread;
//   boost::mutex m_mutex;
//
//private:
//   void showMap(logic::sharedConstMatrix map);
//   void showUnits(logic::sharedConstMatrix map);
//};
//
//} /* namespace view */
//} /* namespace fourFs */
//
//#endif /* fourFs_TERMINAL_H_ */
