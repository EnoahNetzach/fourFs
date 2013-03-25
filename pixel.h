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
   explicit Pixel(unsigned index);
   ~Pixel();

   unsigned index() const;
   double & height();
   const double & height() const;
   bool isBorder() const;
   Environment & environment();
   const Environment & environment() const;
   bool isUnitsEmpty() const;
   bool isUnitsUnique() const;
   unsigned nOfUnits() const;
   void addUnit(Unit & unit);
   bool removeUnit(const Unit & unit);
   void clearUnits();
   unitsList & units();

protected:

private:
   unsigned m_index;
   double m_height;
   bool m_border;
   Environment * m_environment;
   unitsList m_units;
};

} /* namespace FourFs */

#endif /* fourFs_PIXEL_H_ */
