/*
 * environment.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_ENVIRONMENT_H_
#define fourFs_ENVIRONMENT_H_

#include <list>

#include "utilities.hpp"

namespace FourFs
{

class Environment
{
public:
   explicit Environment();
   ~Environment();

   double vivibility();
   void addPixel(Pixel & pixel);
   bool removePixel(Pixel & pixel);
   void clearPixels();
   pixelsConstIterator pixelsBegin() const;
   pixelsConstIterator pixelsEnd() const;

protected:

private:
   double m_vivibility;
   pixelsList m_pixels;
};

} /* namespace FourFs */

#endif /* fourFs_ENVIRONMENT_H_ */
