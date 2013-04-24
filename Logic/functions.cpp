/*
 * functions.hpp
 *
 *  Created on: Apr 22, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_FUNCTIONS_HPP_
#define fourFs_FUNCTIONS_HPP_

#include "functions.h"

using namespace fourFs;
using namespace logic;

extern inline void foo(int i)
{
   std::cout << "FOO " << i << " " << __FILE__ << ":" << __LINE__ <<  std::endl;
}

#endif /* fourFs_FUNCTIONS_HPP_ */
