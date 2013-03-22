/*
 * main.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#include <iostream>

#include "unit.cpp"
#include "state.h"

int main(int argc, char * argv[])
{
   State state;
   state.test = 42;

   Unit unit(state);

	int a=0;
	return 0;
}

