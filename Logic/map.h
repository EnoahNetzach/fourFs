/*
 * terrain.h
 *
 *  Created on: Mar 23, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_MAP_H_
#define fourFs_MAP_H_

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Map
{
   friend class analysis::serialization::SerializeMap;

public:
   Map();
   Map(unsigned width, unsigned height, double range = 3,
       unsigned frequency = 10, double amplitude = 1, unsigned pace = 10,
       unsigned square = 3, unsigned smooth = 4);
   ~Map();

   unsigned height() const;
   unsigned width() const;
   bool empty() const;
   sharedMatrix matrix();
   sharedConstMatrix matrix() const;

protected:

private:
   sharedMatrix m_matrix;
};

} /* namespace logic */
} /* namespace FourFs */

#endif /* fourFs_MAP_H_ */
