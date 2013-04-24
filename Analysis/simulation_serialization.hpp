/*
 * simulation_serialization.hpp
 *
 *  Created on: Apr 24, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_SIMULATION_SERIALIZATION_HPP_
#define fourFs_SIMULATION_SERIALIZATION_HPP_

#include "../Logic/simulation.h"
#include "map_serialization.hpp"
#include "unit_serialization.hpp"

#include <boost/archive/shared_ptr_helper.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

namespace fourFs {
namespace analysis {
namespace serialization {

class SerializeSimulation
{
public:
   SerializeSimulation(logic::Simulation & simulation) : m_simulation(simulation) {}

   template< class Archive >
   void serialize(Archive & ar, unsigned /*v*/)
   {
      ar & m_simulation.m_width;
      ar & m_simulation.m_height;
      ar & m_simulation.m_range;
      ar & m_simulation.m_frequency;
      ar & m_simulation.m_amplitude;
      ar & m_simulation.m_pace;
      ar & m_simulation.m_square;
      ar & m_simulation.m_smooth;
      ar & m_simulation.m_map;
      ar & m_simulation.m_units;
   }

private:
   logic::Simulation & m_simulation;
};


} /* namespace serialization */
} /* namespace analysis */
} /* namespace fourFs */

namespace boost {
namespace serialization {

template< class Archive >
inline void serialize(Archive & ar, fourFs::logic::Simulation & simulation, unsigned /*v*/)
{
   fourFs::analysis::serialization::SerializeSimulation sp(simulation);

   ar & sp;
}

} /* namespace boost */
} /* namespace serialization */

#endif /* fourFs_SIMULATION_SERIALIZATION_HPP_ */
