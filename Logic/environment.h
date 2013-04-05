/*
 * environment.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_ENVIRONMENT_H_
#define fourFs_ENVIRONMENT_H_

#include "../utilities.hpp"

namespace fourFs {
namespace logic {

class Environment
{
public:
   explicit Environment();
   ~Environment();

   double vivibility();
   void addPixel(sharedPixel pixel);
   bool removePixel(sharedPixel pixel);
   void clearPixels();
   pixelConstIterator pixelsBegin() const;
   pixelConstIterator pixelsEnd() const;

protected:

private:
   double m_vivibility;
   pixelsList m_pixels;
};

} /* namespace logic */
} /* namespace fourFs */

#endif /* fourFs_ENVIRONMENT_H_ */
