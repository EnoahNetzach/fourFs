/*
 * terrain.h
 *
 *  Created on: Mar 23, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_TERRAIN_H_
#define fourFs_TERRAIN_H_

#include "matrix.h"
#include "utilities.hpp"

namespace FourFs
{

class Terrain
{
public:
   Terrain(unsigned width, unsigned height);
   ~Terrain();

   unsigned height() const;
   unsigned width() const;
   Matrix & matrix();
   const Matrix & matrix() const;
   void show() const;

protected:

private:
   Matrix m_matrix;
};

} /* namespace FourFs */

#endif /* fourFs_TERRAIN_H_ */
