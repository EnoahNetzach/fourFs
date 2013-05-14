/**
 * @file swarm_serialization.hpp
 *
 * @date May 1, 2013
 * @author Enoah Netzach
 *
 * @brief Provides serialization (save/load) utilities for fourFs::logic::Swarm @c class
 */

#ifndef fourFs_SWARM_SERIALIZATION_HPP_
#define fourFs_SWARM_SERIALIZATION_HPP_

#include "../Logic/matrix.h"

#include <boost/serialization/map.hpp>

#include "../Logic/swarm.h"
#include "unit_serialization.hpp"

namespace fourFs {
namespace analysis {
namespace serialization {

class SerializeSwarm
{
public:
   inline SerializeSwarm(logic::Swarm & swarm) : m_swarm(swarm) {}

   template< class Archive >
   void serialize(Archive & ar, unsigned /*v*/)
   {
      ar & m_swarm.m_units;
      ar & m_swarm.m_nextId;
   }

private:
   logic::Swarm & m_swarm;
};

} /* namespace serialization */
} /* namespace analysis */
} /* namespace fourFs */

namespace boost {
namespace serialization {

template< class Archive >
inline void serialize(Archive & ar, fourFs::logic::Swarm & swarm, unsigned /*v*/)
{
   fourFs::analysis::serialization::SerializeSwarm sp(swarm);

   ar & sp;
}

} /* namespace boost */
} /* namespace serialization */

#endif /* fourFs_SWARM_SERIALIZATION_HPP_ */
