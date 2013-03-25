/*
 * matrix.h
 *
 *  Created on: Mar 22, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_MATRIX_H_
#define fourFs_MATRIX_H_

#include <vector>

#include "utilities.hpp"

namespace FourFs
{

class Matrix
{
   friend class Terrain;

public:
   Matrix(unsigned width, unsigned height);
   ~Matrix();

   unsigned indexFromPosition(unsigned x, unsigned y) const;
   std::pair< unsigned, unsigned > positionFromIndex(unsigned index) const;
   unsigned height() const;
   unsigned width() const;
   unsigned size() const;
   Pixel & pixelAtIndex(unsigned index);
   const Pixel & pixelAtIndex(unsigned index) const;
   Pixel & pixelAtPosition(unsigned x, unsigned y);
   const Pixel & pixelAtPosition(unsigned x, unsigned y) const;
   pixelsList pixelsAroundIndex(unsigned index, unsigned radius);
   const constPixelsList pixelsAroundIndex(unsigned index, unsigned radius) const;
   pixelsList pixelsAroundPosition(unsigned x, unsigned y, unsigned radius);
   const constPixelsList pixelsAroundPosition(unsigned x, unsigned y, unsigned radius) const;

protected:

private:
   unsigned m_height;
   unsigned m_width;
   std::vector< Pixel * > m_pixels;
};

} /* namespace FourFs */

#endif /* fourFs_MATRIX_H_ */
