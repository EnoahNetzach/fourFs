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

class SerializeMap
{
public:
   SerializeMap(logic::Map & map) : m_map(map) {}

   template< class Archive >
   void serialize(Archive & ar, unsigned v)
   {
      ar & m_map.m_matrix;
   }

private:
   logic::Map & m_map;
};

} /* namespace analysis */
} /* namespace fourFs */

namespace boost {
namespace serialization {

using namespace fourFs;
using namespace analysis;
using namespace logic;

template< class Archive >
void serialize(Archive & ar, Map & map, unsigned v)
{
   SerializeMap sp(map);

   ar & sp;
}

template< class Archive >
void load_construct_data(Archive & /*ar*/, Map * map, unsigned /*v*/)
{
   ::new(map) Map(0, 0);
}

} /* namespace boost */
} /* namespace serialization */

#endif /* fourFs_MAP_SERIALIZATION_HPP_ */
