/*
 * pixel_serialization.hpp
 *
 *  Created on: Apr 8, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_PIXEL_SERIALIZATION_HPP_
#define fourFs_PIXEL_SERIALIZATION_HPP_

#include "../Logic/pixel.h"

#include <boost/archive/shared_ptr_helper.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/list.hpp>

namespace fourFs {
namespace analysis {
namespace serialization {

class SerializePixel
{
public:
   SerializePixel(logic::Pixel & pixel) : m_pixel(pixel) {}

   template< class Archive >
   void serialize(Archive & ar, unsigned /*v*/)
   {
      ar & m_pixel.m_index;
      ar & m_pixel.m_height;
      //ar & m_pixel.m_environment;
      ar & m_pixel.m_border;
      ar & m_pixel.m_units;
   }

private:
   logic::Pixel & m_pixel;
};

} /* namespace serialization */
} /* namespace analysis */
} /* namespace fourFs */

namespace boost {
namespace serialization {

template< class Archive >
inline void serialize(Archive & ar, fourFs::logic::Pixel & pixel, unsigned /*v*/)
{
   fourFs::analysis::serialization::SerializePixel sp(pixel);

   ar & sp;
}

template< class Archive >
inline void load_construct_data(Archive & /*ar*/, fourFs::logic:: Pixel * pixel, unsigned /*v*/)
{
   ::new(pixel) fourFs::logic::Pixel(0);
}

} /* namespace boost */
} /* namespace serialization */

#endif /* fourFs_PIXEL_SERIALIZATION_HPP_ */
