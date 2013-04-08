/*
 * unit_serialization.hpp
 *
 *  Created on: Apr 8, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_UNIT_SERIALIZATION_HPP_
#define fourFs_UNIT_SERIALIZATION_HPP_

#include "../Logic/unit.h"

#include <boost/archive/shared_ptr_helper.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

namespace fourFs {
namespace analysis {

class SerializeUnit
{
public:
   SerializeUnit(logic::Unit & unit) : m_unit(unit) {}

   template< class Archive >
   void serialize(Archive & ar, unsigned v)
   {
      ar & m_unit.m_belligerance;
      ar & m_unit.m_fertility;
      ar & m_unit.m_longevity;
      ar & m_unit.m_pixels;
      //ar & m_unit.m_state;
   }

private:
   logic::Unit & m_unit;
};

} /* namespace analysis */
} /* namespace fourFs */

namespace boost {
namespace serialization {

using namespace fourFs;
using namespace analysis;
using namespace logic;

template< class Archive >
void serialize(Archive & ar, Unit & unit, unsigned v)
{
   SerializeUnit sp(unit);

   ar & sp;
}

} /* namespace boost */
} /* namespace serialization */

#endif /* fourFs_UNIT_SERIALIZATION_HPP_ */
