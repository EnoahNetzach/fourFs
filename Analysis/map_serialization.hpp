/*
 * map_serialization.hpp
 *
 *  Created on: Apr 8, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_MAP_SERIALIZATION_HPP_
#define fourFs_MAP_SERIALIZATION_HPP_

#include "../Logic/map.h"

#include <boost/archive/shared_ptr_helper.hpp>
#include <boost/serialization/shared_ptr.hpp>

namespace fourFs {
namespace analysis {
namespace serialization {

class SerializeMap
{
public:
   SerializeMap(logic::Map & map) : m_map(map) {}

   template< class Archive >
   void serialize(Archive & ar, unsigned /*v*/)
   {
      ar & m_map.m_matrix;
   }

private:
   logic::Map & m_map;
};


} /* namespace serialization */
} /* namespace analysis */
} /* namespace fourFs */

namespace boost {
namespace serialization {

template< class Archive >
inline void serialize(Archive & ar, fourFs::logic::Map & map, unsigned /*v*/)
{
   fourFs::analysis::serialization::SerializeMap sp(map);

   ar & sp;
}

} /* namespace boost */
} /* namespace serialization */

#endif /* fourFs_MAP_SERIALIZATION_HPP_ */
