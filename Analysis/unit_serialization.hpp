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
namespace serialization {

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

} /* namespace serialization */
} /* namespace analysis */
} /* namespace fourFs */

namespace boost {
namespace serialization {

template< class Archive >
inline void serialize(Archive & ar, fourFs::logic::Unit & unit, unsigned v)
{
   fourFs::analysis::serialization::SerializeUnit sp(unit);

   ar & sp;
}

} /* namespace boost */
} /* namespace serialization */

#endif /* fourFs_UNIT_SERIALIZATION_HPP_ */
