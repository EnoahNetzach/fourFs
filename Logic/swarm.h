/**
 * @file swarm.h
 *
 * @date May 1, 2013
 * @author Enoah Netzach
 *
 * @brief Definition of fuorFs::logic::Swarm @c class
 */

#ifndef fourFs_SWARM_H_
#define fourFs_SWARM_H_

#include <map>

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Swarm
{
   /**
    * @brief For serialization (save/load) purpose
    */
   friend class analysis::serialization::SerializeSwarm;

public:
   /**
    * @brief The constructor
    */
   explicit Swarm();

   /**
    * @brief Return Swarm size
    * @return The number of Unit%s in this Swarm
    */
   unsigned size() const;
   /**
    * @brief Test whether the Swarm is empty
    * @return @c true if the size() is @c 0, @c false otherwise
    */
   bool empty() const;
   /**
    * @brief Add a Unit in the Swarm
    * @param radius The radius of the Pixel%s' square occupied by the new Unit
    * @param longevity The @a longevity of the new Unit
    * @param fertility The @a fertility of the new Unit
    * @param belligerance The @a belligerance of the new Unit
    * @return A shared reference to the added Unit
    */
   sharedUnit addUnit(unsigned radius, double longevity,
                      double fertility, double belligerance);
   /**
    * @brief Remove a Unit from the Swarm
    * @param id Unique identifier of the referenced Unit
    * @return @c true if the Unit was in the Swarm, @c false otherwise
    */
   bool removeUnit(id_type id);
   /**
    * @brief Remove Unit%s from the Swarm
    * @param num Number of Unit%s to be deleted, if @c 0 or greater than @c size() than
    *    all the Unit%s are removed
    * @return List of removed Unit%s' index
    */
   indexList deleteUnits(unsigned num);
   /**
    * @brief As deleteUnits(0)
    * @return List of removed Unit%s' index
    */
   indexList clearUnits();
   /**
    * @brief Access Unit element
    * @param id Unique identifier of the Unit
    * @return A shared reference to the Unit identified by @a id
    */
   sharedUnit unitFromId(id_type id);
   /**
    * @brief Access Unit element
    * @param id Unique identifier of the Unit
    * @return A const shared reference to the Unit identified by @a id
    */
   const sharedConstUnit unitFromId(id_type id) const;
   /**
    * @brief Access Unit%s
    * @return A map of all the Unit%s in the Swarm keyed by their <a>id</a>s
    */
   unitMap units();

private:
   unitMap m_units;
   id_type m_nextId;
};

} /* namespace logic */
} /* namespace fourFs */

#endif /* fourFs_SWARM_H_ */
