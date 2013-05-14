/**
 * @file map.h
 *
 * @date Mar 23, 2013
 * @author Enoah Netzach
 *
 * @brief Definition of Map @c class
 */

#ifndef fourFs_MAP_H_
#define fourFs_MAP_H_

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Map
{
   /**
    * @brief For serialization (save/load) purpose
    */
   friend class analysis::serialization::SerializeMap;

public:
   /**
    * @brief The constructor. Constructs a Matrix of 0x0
    */
   explicit Map();
   /**
    * @brief The constructor
    * @param width Width of the Matrix contructed
    * @param height Height of the Matrix contructed
    * @param range Affects the number of iterations used to construct the landscape
    * @param frequency Affects the action used in each iteration to construct the landscape
    * @param amplitude Affects the height of each Pixel's in the landscape
    * @param pace Sets the pace of Pixel%s between two iterations
    * @param square Set the radius of Pixel%s' square used in the creation of the landscape pattern
    * @param smooth Set the radius of Pixel%s' square used in the smoothing of the landscape pattern
    */
   Map(unsigned width, unsigned height, double range = 3,
       unsigned frequency = 10, double amplitude = 1, unsigned pace = 10,
       unsigned square = 3, unsigned smooth = 4);

   /**
    * @brief Getter for the Matrix's height field
    * @return A copy of the Matrix's height field
    */
   unsigned height() const;
   /**
    * @brief Getter for the Matrix's width field
    * @return A copy of the Matrix's width field
    */
   unsigned width() const;
   /**
    * @brief Test whether the Map's Matrix is empty
    * @return @c true if the Map's Matrix @a size is @c 0, @c false otherwise
    */
   bool empty() const;
   /**
    * @brief Access Matrix field
    * @return A shared reference to the Matrix
    */
   sharedMatrix matrix();
   /**
    * @brief Access Matrix field
    * @return A const shared reference to the Matrix
    */
   const sharedConstMatrix matrix() const;

private:
   sharedMatrix m_matrix;
};

} /* namespace logic */
} /* namespace FourFs */

#endif /* fourFs_MAP_H_ */
