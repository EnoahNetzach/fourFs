/**
 * @file utilities.hpp
 *
 * @date Mar 22, 2013
 * @author Enoah Netzach
 *
 * @brief Aggregates utilities and class definitions and <c>typedef</c>s
 */

#ifndef fourFs_UTILITIES_HPP_
#define fourFs_UTILITIES_HPP_

#include <iostream>
#include <list>
#include <map>
#include <string>

#include <boost/random.hpp>
#include <boost/random/random_device.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

/**
 * @brief The random number generator engine
 */
static boost::random_device rng;

/**
 * @brief Main namespace for the project
 */
namespace fourFs {

/**
 * @brief Format timer cout operations
 * @param name Name of the execution performed
 * @return A formatted string
 */
inline const char * timerFormat(const char * name)
{
   std::string format = "[Timer] ";
   format += name;
   format += " time: %ws wall, %us user + %ss system = %ts CPU (%p%)";
   return format.c_str();
}

/**
 * @brief Analysis purpose: save/load, ROOT, ..
 */
namespace analysis {

/**
 * @brief Serialize (save/load) every fourFs::logic @c class
 */
namespace serialization {

class SerializeEnvironment;
class SerializeMatrix;
class SerializePixel;
class SerializeSimulation;
class SerializeState;
class SerializeSwarm;
class SerializeMap;
class SerializeUnit;

} /* namespace serialization */
} /* namespace analysis */

/**
 * @brief Manage user interfaces
 */
namespace interfaces {

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

} /* namespace interfaces */

/**
 * @brief The project logic classes
 */
namespace logic {

class Environment;
typedef boost::shared_ptr< Environment > sharedEnvironment;
typedef boost::shared_ptr< const Environment > sharedConstEnvironment;

/**
 * @class Map
 * @brief Constructs the landscape and gives access to it
 */
class Map;
typedef boost::shared_ptr< Map > sharedMap;
typedef boost::shared_ptr< const Map > sharedConstMap;

/**
 * @class Matrix
 * @brief A container for Pixel%s
 */
class Matrix;
typedef boost::shared_ptr< Matrix > sharedMatrix;
typedef boost::shared_ptr< const Matrix > sharedConstMatrix;

/**
 * @class Pixel
 * @brief The smallest part of the landscape
 */
class Pixel;
typedef unsigned index_type;
typedef std::list< index_type > indexList;
typedef boost::shared_ptr< Pixel > sharedPixel;
typedef boost::shared_ptr< const Pixel > sharedConstPixel;
typedef std::list< sharedPixel > pixelList;
typedef pixelList::iterator pixelIterator;
typedef pixelList::const_iterator pixelConstIterator;
typedef std::list< sharedConstPixel > constPixelList;
typedef constPixelList::iterator constPixelIterator;
typedef constPixelList::const_iterator constPixelConstIterator;

class State;
typedef boost::shared_ptr< State > sharedState;
typedef boost::shared_ptr< const State > sharedConstState;

/**
 * @class Simulation
 * @brief The core of the logic's computation
 */
class Simulation;

/**
 * @class Swarm
 * @brief A container for Unit%s
 */
class Swarm;
typedef boost::shared_ptr< Swarm > sharedSwarm;
typedef boost::shared_ptr< Swarm const > sharedConstSwarm;

/**
 * @class Unit
 * @brief The smallest organism living in the landscape
 */
class Unit;
typedef unsigned id_type;
typedef std::list< id_type > idList;
typedef boost::shared_ptr< Unit > sharedUnit;
typedef boost::shared_ptr< const Unit > sharedConstUnit;
typedef std::list< sharedUnit > unitList;
typedef unitList::iterator unitIterator;
typedef unitList::const_iterator unitConstIterator;
typedef std::list< sharedConstUnit > constUnitList;
typedef constUnitList::iterator constUnitIterator;
typedef constUnitList::const_iterator constUnitConstIterator;
typedef std::map< id_type, sharedUnit > unitMap;

} /* namespace logic */

/**
 * @brief For easy and fast prototyping
 */
namespace script
{
} /* namespace script */
} /* namespace fourFs */

#endif /* fourFs_UTILITIES_HPP_ */
