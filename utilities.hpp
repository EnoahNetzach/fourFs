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

#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "logger.h"

static boost::random_device rng;

namespace fourFs {

inline const char * timerFormat(const char * name)
{
   std::string format = "[Timer] ";
   format += name;
   format += " time: %ws wall, %us user + %ss system = %ts CPU (%p%)";
   return format.c_str();
}

namespace analysis {
namespace serialization {

class SerializeEnvironment;
class SerializeMatrix;
class SerializePixel;
class SerializeState;
class SerializeMap;
class SerializeUnit;

} /* namespace serialization */
} /* namespace analysis */

namespace logic {

class Environment;
typedef boost::shared_ptr< Environment > sharedEnvironment;
typedef boost::shared_ptr< const Environment > sharedConstEnvironment;
typedef boost::weak_ptr< Environment > weakEnvironment;
typedef boost::weak_ptr< const Environment > weakConstEnvironment;

class Matrix;
typedef boost::shared_ptr< Matrix > sharedMatrix;
typedef boost::shared_ptr< const Matrix > sharedConstMatrix;
typedef boost::weak_ptr< Matrix > weakMatrix;
typedef boost::weak_ptr< const Matrix > weakConstMatrix;

class Pixel;
typedef boost::shared_ptr< Pixel > sharedPixel;
typedef boost::shared_ptr< const Pixel > sharedConstPixel;
typedef std::list< sharedPixel > pixelsList;
typedef pixelsList::iterator pixelIterator;
typedef pixelsList::const_iterator pixelConstIterator;
typedef std::list< sharedConstPixel > constPixelList;
typedef constPixelList::iterator constPixelIterator;
typedef constPixelList::const_iterator constPixelConstIterator;
typedef boost::weak_ptr< Pixel > weakPixel;
typedef boost::weak_ptr< const Pixel > weakConstPixel;
typedef std::list< weakPixel > weakPixelsList;
typedef weakPixelsList::iterator weakPixelIterator;
typedef weakPixelsList::const_iterator weakPixelConstIterator;
typedef std::list< weakConstPixel > constWeakPixelList;
typedef constWeakPixelList::iterator constWeakPixelIterator;
typedef constWeakPixelList::const_iterator constWeakPixelConstIterator;

class State;
typedef boost::shared_ptr< State > sharedState;
typedef boost::shared_ptr< const State > sharedConstState;

class Map;
typedef boost::shared_ptr< Map > sharedMap;
typedef boost::shared_ptr< const Map > sharedConstMap;

class Unit;
typedef boost::shared_ptr< Unit > sharedUnit;
typedef boost::shared_ptr< const Unit > sharedConstUnit;
typedef std::list< sharedUnit > unitList;
typedef unitList::iterator unitIterator;
typedef unitList::const_iterator unitConstIterator;
typedef std::list< sharedConstUnit > constUnitList;
typedef constUnitList::iterator constUnitIterator;
typedef constUnitList::const_iterator constUnitConstIterator;
typedef boost::weak_ptr< Unit > weakUnit;
typedef boost::weak_ptr< const Unit > weakConstUnit;
typedef std::list< weakUnit > weakUnitList;
typedef weakUnitList::iterator weakUnitIterator;
typedef weakUnitList::const_iterator weakUnitConstIterator;
typedef std::list< weakConstUnit > constWeakUnitList;
typedef constWeakUnitList::iterator constWeakUnitIterator;
typedef constWeakUnitList::const_iterator constWeakUnitConstIterator;

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
