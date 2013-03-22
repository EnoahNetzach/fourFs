/*
 * utilities.hpp
 *
 *  Created on: Mar 22, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_UTILITIES_HPP_
#define fourFs_UTILITIES_HPP_

#include <list>

namespace FourFs
{

class Matrix;
class Pixel;
class State;
class Unit;

typedef std::list< const Pixel * > pixelsList;
typedef pixelsList::iterator pixelsIterator;
typedef pixelsList::const_iterator pixelsConstIterator;

typedef std::list< const Unit * > unitsList;
typedef unitsList::iterator unitsIterator;
typedef unitsList::const_iterator unitsConstIterator;

} // namespace FourFs

#endif /* fourFs_UTILITIES_HPP_ */
