/*
 * matrix.h
 *
 *  Created on: Mar 22, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_MATRIX_H_
#define fourFs_MATRIX_H_

#include <vector>

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Matrix
{
   friend class Map;
   friend class analysis::serialization::SerializeMatrix;

public:
   typedef std::pair< unsigned, unsigned > coordinates;

   Matrix(unsigned width, unsigned height);
   ~Matrix();

   unsigned indexFromPosition(unsigned x, unsigned y) const;
   coordinates positionFromIndex(unsigned index) const;
   unsigned height() const;
   unsigned width() const;
   unsigned size() const;
   sharedPixel pixelAtIndex(unsigned index);
   const sharedConstPixel pixelAtIndex(unsigned index) const;
   sharedPixel pixelAtPosition(unsigned x, unsigned y);
   const sharedConstPixel pixelAtPosition(unsigned x, unsigned y) const;
   pixelList pixelsAroundIndex(unsigned index, unsigned radius);
   const constPixelList pixelsAroundIndex(unsigned index, unsigned radius) const;
   pixelList pixelsAroundPosition(unsigned x, unsigned y, unsigned radius);
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
