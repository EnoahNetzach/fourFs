/*
 * pixel.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_PIXEL_H_
#define fourFs_PIXEL_H_

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Pixel
{
   friend class analysis::serialization::SerializePixel;

public:
   explicit Pixel(unsigned index, bool border = false);
   ~Pixel();

   unsigned index() const;
   double & height();
   const double & height() const;
   bool isBorder() const;
   bool isUnitsEmpty() const;
   bool isUnitsUnique() const;
   unsigned nOfUnits() const;
   void addUnit(id_type id);
   bool removeUnit(id_type id);
   void clearUnits();
   bool hasUnit(id_type id);
   idList units() const;
//   sharedEnvironment environment();
//   sharedConstEnvironment environment() const;

protected:

private:
   const unsigned m_index;
   double m_height;
   bool m_border;
   idList m_units;
//   sharedEnvironment m_environment;
};

} /* namespace logic */
} /* namespace fourFs */

#endif /* fourFs_PIXEL_H_ */
