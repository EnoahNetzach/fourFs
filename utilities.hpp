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

#include <list>

#include <boost/random/random_device.hpp>
#include <boost/shared_ptr.hpp>

static boost::random_device rng;

namespace FourFs
{

class Environment;
class Matrix;
class Pixel;
class State;
class Terrain;
class Unit;

typedef boost::shared_ptr< Environment > sharedEnvironment;
typedef boost::shared_ptr< const Environment > sharedConstEnvironment;

typedef boost::shared_ptr< Pixel > sharedPixel;
typedef boost::shared_ptr< const Pixel > sharedConstPixel;

typedef std::list< sharedPixel > pixelsList;
typedef pixelsList::iterator pixelsIterator;
typedef pixelsList::const_iterator pixelsConstIterator;

typedef std::list< sharedConstPixel > constPixelsList;
typedef constPixelsList::iterator constPixelsIterator;
typedef constPixelsList::const_iterator constPixelsConstIterator;

typedef boost::shared_ptr< State > sharedState;
typedef boost::shared_ptr< const State > sharedConstState;

typedef boost::shared_ptr< Unit > sharedUnit;
typedef boost::shared_ptr< const Unit > sharedConstUnit;

typedef std::list< sharedUnit > unitsList;
typedef unitsList::iterator unitsIterator;
typedef unitsList::const_iterator unitsConstIterator;

} // namespace FourFs

#endif /* fourFs_UTILITIES_HPP_ */
