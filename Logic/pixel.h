/**
 * @file pixel.h
 *
 * @date Mar 20, 2013
 * @author Enoah Netzach
 *
 * @brief Definition of fourFs::logic::Pixel @c class
 */

#ifndef fourFs_PIXEL_H_
#define fourFs_PIXEL_H_

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Pixel
{
   /**
    * @brief For serialization (save/load) purpose
    */
   friend class analysis::serialization::SerializePixel;

public:
   /**
    * @brief The constructor
    * @param index The unique identifier of this Pixel in the containing Matrix
    * @param border Not implemented yet
    */
   explicit Pixel(index_type index, bool border = false);

   /**
    * @brief Getter for index field
    * @return A copy of the index field
    */
   unsigned index() const;
   /**
    * @brief Access height field
    * @return A reference to height field
    */
   double & height();
   /**
    * @brief Access height field
    * @return A const reference to height field
    */
   const double & height() const;
   /**
    * @brief Not implemented yet
    * @return
    */
   bool isBorder() const;
   /**
    * @brief Not implemented yet
    * @return
    */
   bool isUnitsEmpty() const;
   /**
    * @brief Not implemented yet
    * @return
    */
   bool isUnitsUnique() const;
   /**
    * @return Number of Unit%s placed on this Pixel
    */
   unsigned nOfUnits() const;
   /**
    * @brief Add a Unit placed on this Pixel
    * @param id Unique identifier of the referenced Unit
    */
   void addUnit(id_type id);
   /**
    * @brief Remove a Unit placed on this Pixel
    * @param id Unique identifier of the referenced Unit
    * @return @c true if the Unit was placed on this Pixel, @c false otherwise
    */
   bool removeUnit(id_type id);
   /**
    * @brief Remove all the Unit%s placed on this Pixel
    */
   void clearUnits();
   /**
    * @brief Check if a Unit is placed on this Pixel
    * @param id Unique identifier of the referenced Unit
    * @return @c true if the Unit is present, @c false otherwise
    */
   bool hasUnit(id_type id);
   /**
    * @brief Access Unit%s' id list
    * @return A list of all the Unit%s placed on this Pixel
    */
   idList units() const;
//   sharedEnvironment environment();
//   sharedConstEnvironment environment() const;

private:
   const index_type m_index;
   double m_height;
   bool m_border;
   idList m_units;
//   sharedEnvironment m_environment;
};

} /* namespace logic */
} /* namespace fourFs */

#endif /* fourFs_PIXEL_H_ */
