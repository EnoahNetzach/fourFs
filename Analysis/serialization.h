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

bool save(logic::sharedConstMap map);

logic::sharedMap load();

} /* namespace serialization */
} /* namespace analysis */
} /* namespace fourFs */

#endif /* fourFs_SERIALIZATION_H_ */
