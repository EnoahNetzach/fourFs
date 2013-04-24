/*
 * logger.h
 *
 *  Created on: Apr 10, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_LOGGER_H_
#define fourFs_LOGGER_H_

#include <iostream>

namespace fourFs {

class Logger
{
public:
   Logger();
   ~Logger();

   static void verbose(bool v);
   static bool verbose();

   template< typename T >
   Logger & operator<<(const T & v)
   {
      if (m_verbose)
      {
         std::clog << v;
      }

      return * this;
   }

protected:

private:
   static bool m_verbose;
};

} /* namespace fourFs */

#endif /* fourFs_LOGGER_H_ */
