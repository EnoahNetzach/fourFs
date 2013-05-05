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
   friend class analysis::serialization::SerializeUnit;

public:
   explicit Unit(id_type id, unsigned radius);
   ~Unit();

   id_type id() const;
   unsigned & radius();
   const unsigned & radius() const;
   static unsigned fieldOfView();
   const double & longevity() const;
   const double & fertility() const;
   const double & belligerance() const;
   void addPixel(index_type index);
   bool removePixel(index_type index);
   void clearPixels();
   bool hasPixel(index_type index);
   indexList pixels() const;
   void centralPixel(index_type index);
   index_type centralPixel() const;
//   sharedState state();
//   sharedConstState state() const;

protected:

private:
   const id_type m_id;
   unsigned m_radius;
   double m_belligerance;
   double m_fertility;
   double m_longevity;
   indexList m_pixels;
   index_type m_centralPixel;
   sharedState m_state;
};

} /* namespace logic */
} /* namespace FourFs */

#endif /* fourFs_UNIT_H_ */
