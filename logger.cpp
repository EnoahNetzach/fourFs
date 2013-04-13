/*
 * logger.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: Enoah Netzach
 */

#include "logger.h"

using namespace fourFs;

bool Logger::m_verbose = false;

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::verbose(bool v)
{
   m_verbose = v;
}

bool Logger::verbose()
{
   return m_verbose;
}
