/*
 * mapviewer.h
 *
 *  Created on: Apr 4, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_MAPVIEWER_H_
#define fourFs_MAPVIEWER_H_

#include "../Logic/utilities.hpp"

namespace fourFs {
namespace view {

class MapViewer
{
public:
   MapViewer(const logic::Map & map);
   ~MapViewer();


};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_MAPVIEWER_H_ */
