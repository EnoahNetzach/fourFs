/*
 * utilities.hpp
 *
 *  Created on: Mar 22, 2013
 *      Author: Enoah Netzach
 *
 *   Description:
 *
 */

#ifndef fourFs_UTILITIES_HPP_
#define fourFs_UTILITIES_HPP_

#include <iostream>
#include <list>
#include <string>

#include <boost/random/random_device.hpp>
#include <boost/shared_ptr.hpp>

static boost::random_device rng;

namespace fourFs {
inline const char * timerFormat(const char * name)
{
   std::string format = name;
   format += " time: %ws wall, %us user + %ss system = %ts CPU (%p%)";
   return format.c_str();
}

namespace logic {

class Environment;
typedef boost::shared_ptr< Environment > sharedEnvironment;
typedef boost::shared_ptr< const Environment > sharedConstEnvironment;

class Matrix;

typedef boost::shared_ptr< Matrix > sharedMatrix;
typedef boost::shared_ptr< const Matrix > sharedConstMatrix;

class Pixel;
typedef boost::shared_ptr< Pixel > sharedPixel;
typedef boost::shared_ptr< const Pixel > sharedConstPixel;
typedef std::list< sharedPixel > pixelsList;
typedef pixelsList::iterator pixelIterator;
typedef pixelsList::const_iterator pixelConstIterator;
typedef std::list< sharedConstPixel > constPixelList;
typedef constPixelList::iterator constPixelIterator;
typedef constPixelList::const_iterator constPixelConstIterator;

class State;
typedef boost::shared_ptr< State > sharedState;
typedef boost::shared_ptr< const State > sharedConstState;

class Map;

class Unit;
typedef boost::shared_ptr< Unit > sharedUnit;
typedef boost::shared_ptr< const Unit > sharedConstUnit;
typedef std::list< sharedUnit > unitList;
typedef unitList::iterator unitIterator;
typedef unitList::const_iterator unitConstIterator;

} /* namespace logic */

namespace view {

typedef enum
{
   _openGL = 1L << 0,
   _terminal = 1L << 1
} Option;
static const Option openGL = _openGL;
static const Option terminal = _terminal;
typedef int Options;

class Interface_base;
typedef boost::shared_ptr< Interface_base > sharedInterface;
typedef std::list< sharedInterface > interfaceList;

} /* namespace view */
} /* namespace FourFs */

#endif /* fourFs_UTILITIES_HPP_ */
