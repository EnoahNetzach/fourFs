/*
 * pixel.h
 *
 *  Created on: Mar 20, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_PIXEL_H_
#define fourFs_PIXEL_H_

namespace FourFs
{

class Pixel
{
public:
   explicit Pixel();
   ~Pixel();

   const unsigned & position() const;
   bool isBorder() const;

protected:

private:
   unsigned m_position;
   bool m_border;
   // TODO m_linkedEnvironment [&]
   // TODO m_linkedUnits [&]
};

} /* namespace FourFs */

#endif /* fourFs_PIXEL_H_ */
