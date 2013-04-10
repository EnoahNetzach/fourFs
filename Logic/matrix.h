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
   Matrix(unsigned width, unsigned height);
   ~Matrix();

   unsigned indexFromPosition(unsigned x, unsigned y) const;
   std::pair< unsigned, unsigned > positionFromIndex(unsigned index) const;
   unsigned height() const;
   unsigned width() const;
   unsigned size() const;
   sharedPixel pixelAtIndex(unsigned index);
   sharedConstPixel pixelAtIndex(unsigned index) const;
   sharedPixel pixelAtPosition(unsigned x, unsigned y);
   sharedConstPixel pixelAtPosition(unsigned x, unsigned y) const;
   pixelsList pixelsAroundIndex(unsigned index, unsigned radius);
   const constPixelList pixelsAroundIndex(unsigned index, unsigned radius) const;
   pixelsList pixelsAroundPosition(unsigned x, unsigned y, unsigned radius);
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
