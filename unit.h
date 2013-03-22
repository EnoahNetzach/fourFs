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

   unsigned longevity() const;
   unsigned fertility() const;
   unsigned belligerance() const;
   void addPixel(const Pixel & pixel);
   bool removePixel(const Pixel & pixel);
   void clearPixels();
   pixelsConstIterator pixelsBegin() const;
   pixelsConstIterator pixelsEnd() const;
   State & state();
   const State & state() const;

protected:

private:
   static unsigned m_area;
   static unsigned m_fieldOfView;
   double m_longevity;
   double m_fertility;
   double m_belligerance;
   pixelsList m_pixels;
   State * m_state;

};

} /* namespace FourFs */

#endif /* fourFs_UNIT_H_ */
