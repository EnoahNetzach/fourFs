/*
 * unit.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_UNIT_H_
#define fourFs_UNIT_H_

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Unit
{
public:
   explicit Unit();
   ~Unit();

   static unsigned radius();
   static unsigned fieldOfView();
   const double & longevity() const;
   const double & fertility() const;
   const double & belligerance() const;
   void addPixel(sharedPixel pixel);
   bool removePixel(sharedPixel pixel);
   void clearPixels();
   pixelConstIterator pixelsBegin() const;
   pixelConstIterator pixelsEnd() const;
   sharedState state();
   sharedConstState state() const;

protected:

private:
   double m_belligerance;
   double m_fertility;
   double m_longevity;
   pixelsList m_pixels;
   sharedState m_state;
};

} /* namespace logic */
} /* namespace FourFs */

#endif /* fourFs_UNIT_H_ */
