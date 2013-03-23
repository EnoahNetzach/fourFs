/*
 * unit.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_UNIT_H_
#define fourFs_UNIT_H_

#include <list>

#include "utilities.hpp"

namespace FourFs
{

class Unit
{
public:
   explicit Unit();
   ~Unit();

   static unsigned radius();
   static unsigned fieldOfView();
   double longevity() const;
   double fertility() const;
   double belligerance() const;
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
