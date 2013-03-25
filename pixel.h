/*
 * pixel.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_PIXEL_H_
#define fourFs_PIXEL_H_

#include "utilities.hpp"

namespace FourFs
{

class Pixel
{
public:
   explicit Pixel(unsigned index, bool border = false);
   ~Pixel();

   unsigned index() const;
   double & height();
   const double & height() const;
   bool isBorder() const;
   sharedEnvironment environment();
   sharedConstEnvironment environment() const;
   bool isUnitsEmpty() const;
   bool isUnitsUnique() const;
   unsigned nOfUnits() const;
   void addUnit(sharedUnit unit);
   bool removeUnit(sharedConstUnit unit);
   void clearUnits();
   unitsList & units();

protected:

private:
   unsigned m_index;
   double m_height;
   bool m_border;
   sharedEnvironment m_environment;
   unitsList m_units;
};

} /* namespace FourFs */

#endif /* fourFs_PIXEL_H_ */
