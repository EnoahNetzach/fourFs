/*
 * mapviewer.h
 *
 *  Created on: Apr 4, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_MAPVIEWER_H_
#define fourFs_MAPVIEWER_H_

#include <list>

#include "../utilities.hpp"

namespace fourFs {
namespace view {

class MapViewer
{
public:
   MapViewer(const logic::Map & map, Options op);
   ~MapViewer();

   void show() const;

protected:

private:
   const logic::Map & m_map;
   interfaceList m_interfaces;
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_MAPVIEWER_H_ */
