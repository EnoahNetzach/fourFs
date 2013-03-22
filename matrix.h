/*
 * matrix.h
 *
 *  Created on: Mar 22, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_MATRIX_H_
#define fourFs_MATRIX_H_

#include <boost/container/flat_map.hpp>

#include "pixel.h"

namespace FourFs
{

class Matrix
{
public:
   Matrix();
   ~Matrix();

protected:

private:
   boost::container::flat_map< unsigned, Pixel * > m_pixels;
};

} /* namespace FourFs */

#endif /* fourFs_MATRIX_H_ */
