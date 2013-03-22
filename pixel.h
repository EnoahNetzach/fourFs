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
   explicit Pixel(unsigned index);
   ~Pixel();

   unsigned test;

   unsigned index() const;
   bool isBorder() const;

protected:

private:
   unsigned m_index;
   bool m_border;
   // TODO m_environment [&]
   // TODO m_units [&]
};

} /* namespace FourFs */

#endif /* fourFs_PIXEL_H_ */
