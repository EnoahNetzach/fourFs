/*
 * swarm.h
 *
 *  Created on: May 1, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_SWARM_H_
#define fourFs_SWARM_H_

#include <map>

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Swarm
{
   friend class analysis::serialization::SerializeSwarm;

public:
   explicit Swarm();
   ~Swarm();

   unsigned size() const;
   bool empty() const;
   sharedUnit addUnit(unsigned radius);
   void removeUnit(id_type id);
   indexList deleteUnits(unsigned num);
   indexList clearUnits();
   sharedUnit unitFromId(id_type id);
   const sharedConstUnit unitFromId(id_type id) const;
   unitMap units();

protected:

private:
   unitMap m_units;
   id_type m_nextId;
};

} /* namespace logic */
} /* namespace fourFs */
#endif /* fourFs_SWARM_H_ */
