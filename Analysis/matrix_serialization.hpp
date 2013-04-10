/*
 * matrix_serialization.hpp
 *
 *  Created on: Apr 8, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_MATRIX_SERIALIZATION_HPP_
#define fourFs_MATRIX_SERIALIZATION_HPP_

#include "../Logic/matrix.h"

#include <boost/serialization/vector.hpp>

namespace fourFs {
namespace analysis {
namespace serialization {

class SerializeMatrix
{
public:
   inline SerializeMatrix(logic::Matrix & matrix) : m_matrix(matrix) {}

   template< class Archive >
   void serialize(Archive & ar, unsigned v)
   {
      ar & m_matrix.m_height;
      ar & m_matrix.m_width;
      ar & m_matrix.m_pixels;
   }

private:
   logic::Matrix & m_matrix;
};

} /* namespace serialization */
} /* namespace analysis */
} /* namespace fourFs */

namespace boost {
namespace serialization {

template< class Archive >
inline void serialize(Archive & ar, fourFs::logic::Matrix & matrix, unsigned v)
{
   fourFs::analysis::serialization::SerializeMatrix sp(matrix);

   ar & sp;
}

template< class Archive >
inline void load_construct_data(Archive & /*ar*/, fourFs::logic::Matrix * matrix, unsigned /*v*/)
{
   ::new(matrix) fourFs::logic::Matrix(0, 0);
}

} /* namespace boost */
} /* namespace serialization */

#endif /* fourFs_MATRIX_SERIALIZATION_HPP_ */
