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
public:/*
 * range ~2.5
 *
 * frequency 10
 *
 * amplitude ~0.3
 *
 * pace 4
 *
 * square 4
 *
 * smooth 3
 */
   Terrain(unsigned width, unsigned height, double range = 2.5,
           unsigned frequency = 10, double amplitude = 0.3, unsigned pace = 4,
           unsigned square = 4, unsigned smooth = 3);
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
