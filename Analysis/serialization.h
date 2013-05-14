/**
 * @file serialization.h
 *
 * @date Apr 10, 2013
 * @author Enoah Netzach
 *
 * @brief Serialization (save/load) routines
 */

#ifndef fourFs_SERIALIZATION_H_
#define fourFs_SERIALIZATION_H_

#include "../utilities.hpp"

namespace fourFs {
namespace analysis {
namespace serialization {

/**
 * @brief Saves the current state of logic::Simulation to a file
 * @param simulation The current logic::Simulation to be saved
 * @return @c true if the state was saved, @c false otherwise
 */
bool save(const logic::Simulation & simulation);

/**
 * @brief Loads a saved logic::Simulation from a file
 * @param simulation The logic::Simulation that wiill be overwritten by a previously saved state
 */
void load(logic::Simulation & simulation);

} /* namespace serialization */
} /* namespace analysis */
} /* namespace fourFs */

#endif /* fourFs_SERIALIZATION_H_ */
