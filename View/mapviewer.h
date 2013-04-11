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
   MapViewer(Options op);
   ~MapViewer();

   void show(logic::sharedConstMap map) const;

protected:

private:
   interfaceList m_interfaces;
};

} /* namespace view */
} /* namespace fourFs */

#endif /* fourFs_MAPVIEWER_H_ */
