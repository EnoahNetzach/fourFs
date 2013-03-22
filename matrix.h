/*
 * matrix.h
 *
 *  Created on: Mar 22, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_MATRIX_H_
#define fourFs_MATRIX_H_

#include <vector>

#include "pixel.h"

namespace FourFs
{

class Matrix
{
public:
   Matrix(unsigned width, unsigned height);
   ~Matrix();

   unsigned indexFromPosition(unsigned x, unsigned y);
   std::pair< unsigned, unsigned > positionFromIndex(unsigned index);
   unsigned height() const;
   unsigned width() const;
   Pixel & pixelAtIndex(unsigned index);
   Pixel & pixelAtPosition(unsigned x, unsigned y);

protected:

private:
   unsigned m_height;
   unsigned m_width;
   std::vector< Pixel * > m_pixels;
};

} /* namespace FourFs */

#endif /* fourFs_MATRIX_H_ */
