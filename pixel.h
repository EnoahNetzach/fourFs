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

class Unit;

class Pixel
{
public:
   explicit Pixel(unsigned index);
   ~Pixel();

   unsigned test;

   unsigned index() const;
   bool isBorder() const;
   void addUnit(const Unit & unit);
   bool removeUnit(const Unit & unit);
   unitsList units();

protected:

private:
   unsigned m_index;
   bool m_border;
   // TODO m_environment [&]
   unitsList m_units;
};

} /* namespace FourFs */

#endif /* fourFs_PIXEL_H_ */
