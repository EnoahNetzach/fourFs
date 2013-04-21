/*
 * serialization.h
 *
 *  Created on: Apr 10, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_SERIALIZATION_H_
#define fourFs_SERIALIZATION_H_

#include "../utilities.hpp"

namespace fourFs {
namespace analysis {
namespace serialization {

/**
 * Saves the current state of logic::Map to a file
 *
 * @param map
 * @return
 */
bool save(logic::sharedConstMap map);

/**
 * Loads a saved logic::Map from a file
 *
 * @param map
 */
void load(logic::sharedMap map);

} /* namespace serialization */
} /* namespace analysis */
} /* namespace fourFs */

#endif /* fourFs_SERIALIZATION_H_ */
