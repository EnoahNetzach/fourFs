/*
 * serializer.h
 *
 *  Created on: Apr 8, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_SERIALIZER_H_
#define fourFs_SERIALIZER_H_

#include <boost/filesystem.hpp>

#include "../utilities.hpp"

namespace fourFs {
namespace analysis {

class Serializer
{
public:
   Serializer(const char * basePath);
   ~Serializer();

   bool save(const logic::Map & map) const;
   logic::Map load() const;

protected:

private:
   boost::filesystem::path m_basePath;
};

} /* namespace analysis */
} /* namespace fourFs */

#endif /* fourFs_SERIALIZER_H_ */
