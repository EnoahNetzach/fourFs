/**
 * @file unit.h
 *
 * @date Mar 20, 2013
 * @author Enoah Netzach
 *
 * @brief Definition of Unit @c class
 */

#ifndef fourFs_UNIT_H_
#define fourFs_UNIT_H_

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Unit
{
   /**
    * @brief For serialization (save/load) purpose
    */
   friend class analysis::serialization::SerializeUnit;

public:
   /**
    * @brief The constructor
    * @param id The unique identifier of this Unit in the containing Swarm
    * @param radius The radius of the Pixel%s' square occupied by this Unit
    * @param longevity The field value
    * @param fertility The field value
    * @param belligerance The field value
    */
   explicit Unit(id_type id, unsigned radius, double longevity,
                 double fertility, double belligerance);

   /**
    * @brief Getter for id field
    * @return A copy of the id field
    */
   id_type id() const;
   /**
    * @brief Access radius field
    * @return A reference to radius field
    */
   unsigned & radius();
   /**
    * @brief Access radius field
    * @return A const reference to radius field
    */
   const unsigned & radius() const;
   /**
    * @brief Not fully implemented yet
    * @return The radius of the Pixel%s' square visible to this Unit
    */
   static unsigned fieldOfView();
   /**
    * @brief Access longevity field
    * @return A copy of the longevity field
    */
   double longevity() const;
   /**
    * @brief Access fertility field
    * @return A copy of the fertility field
    */
   double fertility() const;
   /**
    * @brief Access belligerance field
    * @return A copy of the belligerance field
    */
   double belligerance() const;
   /**
    * @brief Add a Pixel placed under this Unit
    * @param index Unique identifier of the referenced Pixel
    */
   void addPixel(index_type index);
   /**
    * @brief Remove a Pixel placed under this Unit
    * @param id Unique identifier of the referenced Pixel
    * @return @c true if the Pixel was placed under this Unit, @c false otherwise
    */
   bool removePixel(index_type index);
   /**
    * @brief Remove all the Pixel%s placed under this Unit
    */
   void clearPixels();
   /**
    * @brief Check if a Pixel is placed under this Unit
    * @param id Unique identifier of the referenced Pixel
    * @return @c true if the Pixel is present, @c false otherwise
    */
   bool hasPixel(index_type index);
   /**
    * @brief Access Pixel%s' index list
    * @return A list of all the Pixel%s placed under this Unit
    */
   indexList pixels() const;
   /**
    * @brief Set central Pixel field
    * @param index Unique identifier of the referenced Pixel
    */
   void centralPixel(index_type index);
   /**
    * @brief Access central Pixel field
    * @return A copy of the central Pixel index
    */
   index_type centralPixel() const;
//   sharedState state();
//   sharedConstState state() const;

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
