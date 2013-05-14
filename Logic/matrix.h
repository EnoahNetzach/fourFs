/**
 * @file matrix.h
 *
 * @date Mar 22, 2013
 * @author Enoah Netzach
 *
 * @brief Definition of Matrix @c class
 */

#ifndef fourFs_MATRIX_H_
#define fourFs_MATRIX_H_

#include <vector>

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Matrix
{
   //friend class Map;
   /**
    * @brief For serialization (save/load) purpose
    */
   friend class analysis::serialization::SerializeMatrix;

public:
   typedef std::pair< unsigned, unsigned > coordinates;

   /**
    * @brief The constructor
    * @param width Set the Matrix width
    * @param height Set the Matrix height
    */
   explicit Matrix(unsigned width, unsigned height);
   ~Matrix();

   /**
    * @brief Convert Pixel's coordinates to index
    * @param x Abscissa of the Pixel
    * @param y Ordinate of the Pixel
    * @return The index of the pixel at (@a x, @a y)
    */
   index_type indexFromPosition(unsigned x, unsigned y) const;
   /**
    * @brief Convert Pixel's index to coordinates
    * @param index Unique identifier of the Pixel
    * @return An std::pair containing the Pixel's coordinates
    */
   coordinates positionFromIndex(index_type index) const;
   /**
    * @brief Getter for height field
    * @return A copy of the height field
    */
   unsigned height() const;
   /**
    * @brief Getter for width field
    * @return A copy of the width field
    */
   unsigned width() const;
   /**
    * @brief Return Matrix size
    * @return The number of Pixel%s in this Matrix
    */
   unsigned size() const;
   /**
    * @brief Access Pixel element
    * @param index Unique identifier of the Pixel
    * @return A shared reference to the Pixel identified by @a index
    */
   sharedPixel pixelAtIndex(index_type index);
   /**
    * @brief Access Pixel element
    * @param index Unique identifier of the Pixel
    * @return A const shared reference to the Pixel identified by @a index
    */
   const sharedConstPixel pixelAtIndex(index_type index) const;
   /**
    * @brief Access Pixel element
    * @param x Abscissa of the Pixel
    * @param y Ordinate of the Pixel
    * @return A shared reference to the Pixel at (@a x, @a y)
    */
   sharedPixel pixelAtPosition(unsigned x, unsigned y);
   /**
    * @brief Access Pixel element
    * @param x Abscissa of the Pixel
    * @param y Ordinate of the Pixel
    * @return A const shared reference to the Pixel at (@a x, @a y)
    */
   const sharedConstPixel pixelAtPosition(unsigned x, unsigned y) const;
   /**
    * @brief Access Pixel elements
    * @param index Unique identifier of the central Pixel
    * @param radius Radius of the square of Pixel%s accessed
    * @return A list of shared references to the square of Pixel%s around the central Pixel
    *    given by @a index. Only existing Pixel%s are listed
    */
   pixelList pixelsAroundIndex(index_type index, unsigned radius);
   /**
    * @brief Access Pixel elements
    * @param index Unique identifier of the central Pixel
    * @param radius Radius of the square of Pixel%s accessed
    * @return A list of const shared references to the square of Pixel%s around the central Pixel
    *    given by @a index. Only existing Pixel%s are listed
    */
   const constPixelList pixelsAroundIndex(index_type index, unsigned radius) const;
   /**
    * @brief Access Pixel elements
    * @param x Abscissa of the central Pixel
    * @param y Ordinate of the central Pixel
    * @param radius Radius of the square of Pixel%s accessed
    * @return A list of shared references to the square of Pixel%s around the central Pixel
    *    at (@a x, @a y). Only existing Pixel%s are listed
    */
   pixelList pixelsAroundPosition(unsigned x, unsigned y, unsigned radius);
   /**
    * @brief Access Pixel elements
    * @param x Abscissa of the central Pixel
    * @param y Ordinate of the central Pixel
    * @param radius Radius of the square of Pixel%s accessed
    * @return A list of const shared references to the square of Pixel%s around the central Pixel
    *    at (@a x, @a y). Only existing Pixel%s are listed
    */
   const constPixelList pixelsAroundPosition(unsigned x, unsigned y, unsigned radius) const;

protected:

private:
   unsigned m_height;
   unsigned m_width;
   std::vector< sharedPixel > m_pixels;
};

} /* namespace logic */
} /* namespace fourFs */

#endif /* fourFs_MATRIX_H_ */
