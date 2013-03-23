/*
 * unit.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_UNIT_H_
#define fourFs_UNIT_H_

#include <list>

#include "matrix.h"

namespace FourFs
{

class Pixel;
class State;

class Unit
{
public:
   explicit Unit();
   ~Unit();

   static unsigned radius();
   static unsigned fieldOfView();
   unsigned longevity() const;
   unsigned fertility() const;
   unsigned belligerance() const;
   void addPixel(Pixel & pixel);
   bool removePixel(Pixel & pixel);
   void clearPixels();
   pixelsConstIterator pixelsBegin() const;
   pixelsConstIterator pixelsEnd() const;
   State & state();
   const State & state() const;

protected:

private:
   double m_longevity;
   double m_fertility;
   double m_belligerance;
   pixelsList m_pixels;
   State * m_state;

};

} /* namespace FourFs */

#endif /* fourFs_UNIT_H_ */
