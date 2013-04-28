/*
 * classes.hpp
 *
 *  Created on: Apr 28, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_CLASSES_HPP_
#define fourFs_CLASSES_HPP_

#include <algorithm>
#include <list>
#include <python2.7/Python.h>

#include <boost/python.hpp>
#include <boost/smart_ptr.hpp>

#include "../utilities.hpp"
#include "../Logic/map.h"
#include "../Logic/matrix.h"
#include "../Logic/pixel.h"
#include "../Logic/unit.h"

#define GET_REF(type, className, function) \
   type get_ ## function ## className(className & c) \
   { \
      return c.function(); \
   }

#define SET_REF(type, className, function) \
   void set_ ## function ## className(className & c, type n) \
   { \
      c.function() = n; \
   }

#define GET_SET_REF(type, className, function) \
   GET_REF(type, className, function) \
   SET_REF(type, className, function)

template< class T >
struct listwrap
{
   typedef T list_type;
   typedef typename list_type::value_type value_type;
   typedef typename list_type::iterator iter_type;

   static void add(list_type & x, value_type const & v)
   {
      x.push_back(v);
   }

   static bool in(list_type const & x, value_type const & v)
   {
      return std::find(x.begin(), x.end(), v) != x.end();
   }

   static int index(list_type const & x, value_type const & v)
   {
      int i = 0;
      for(typename list_type::const_iterator it=x.begin(); it!=x.end(); ++it,++i)
      {
         if( *it == v ) return i;
      }

      PyErr_SetString(PyExc_ValueError, "Value not in the list");
      throw boost::python::error_already_set();
   }

   static void del(list_type & x, int i)
   {
      if( i<0 ) i += x.size();

      iter_type it = x.begin();
      for (int pos = 0; pos < i; ++pos) ++it;

      if( i >= 0 && i < (int)x.size() )
      {
         x.erase(it);
      }
      else
      {
         PyErr_SetString(PyExc_IndexError, "Index out of range");
         boost::python::throw_error_already_set();
      }
   }

   static value_type & get(list_type & x, int i)
   {
      if( i < 0 ) i += x.size();

      if( i >= 0 && i < (int)x.size() )
      {
         iter_type it = x.begin();
         for(int pos = 0; pos < i; ++pos) ++it;
         return * it;
      }
      else
      {
         PyErr_SetString(PyExc_IndexError, "Index out of range");
         throw boost::python::error_already_set();
      }
   }

   static void set(list_type & x, int i, value_type const & v)
   {
      if( i < 0 ) i += x.size();

      if( i >= 0 && i < (int)x.size() )
      {
         iter_type it = x.begin();
         for(int pos = 0; pos < i; ++pos) ++it;
         *it = v;
      }
      else
      {
         PyErr_SetString(PyExc_IndexError, "Index out of range");
         boost::python::throw_error_already_set();
      }
   }
};

#define EXPORT_STD_LIST(type, typeName) \
   boost::python::class_< type >(typeName) \
      .def("__len__", & type::size) \
      .def("clear", & type::clear) \
      .def("append", & listwrap< type >::add, \
           boost::python::with_custodian_and_ward< 1, 2 >()) \
      .def("__getitem__", & listwrap< type >::get, \
           boost::python::return_value_policy< \
              boost::python::copy_non_const_reference >()) \
      .def("__setitem__", & listwrap< type >::set, \
           boost::python::with_custodian_and_ward< 1, 2 >()) \
      .def("__delitem__", & listwrap< type >::del) \
      .def("__contains__", & listwrap< type >::in) \
      .def("__iter__", iterator< type >()) \
      .def("index", & listwrap< type >::index) \
   ;

#define EXPORT_STD_LIST_OF_TYPE(type, typeName) EXPORT_STD_LIST(std::list< type >, typeName)

template< class T >
struct pairwarp
{
   typedef T pair_type;
   typedef typename pair_type::first_type first_type;
   typedef typename pair_type::second_type second_type;

   static first_type first(pair_type & x) { return x.first; }
   static second_type second(pair_type & x) { return x.second; }
};

#define EXPORT_STD_PAIR(type, typeName) \
   boost::python::class_< type >(typeName) \
      .def("first", & pairwarp< type >::first) \
      .def("second", & pairwarp< type >::second) \
   ;

#define EXPORT_STD_PAIR_OF_TYPE(type1, type2, typeName) EXPORT_STD_PAIR(std::pair< type1, type2 >, typeName)

/*
 * Python exposition
 */

int randInt(int a, int b)
{
   return boost::random::uniform_int_distribution<>(a, b)(rng);
}

double randReal(double a, double b)
{
   return boost::random::uniform_real_distribution<>(a, b)(rng);
}

double rand01()
{
   return boost::random::uniform_01<>()(rng);
}

using namespace fourFs::logic;

GET_SET_REF(double, Pixel, height)
GET_SET_REF(unsigned, Unit, radius)
GET_REF(double, Unit, longevity)
GET_REF(double, Unit, fertility)
GET_REF(double, Unit, belligerance)

BOOST_PYTHON_MODULE(fourFs)
{
   using namespace boost::python;

   // random generators
   def("randInt", randInt);
   def("randReal", randReal);
   def("rand01", rand01);

   EXPORT_STD_LIST(pixelList, "PixelList")
   EXPORT_STD_LIST(unitList, "UnitList")

   EXPORT_STD_PAIR(Matrix::coordinates, "Pos")

   class_< Map, sharedMap, boost::noncopyable >("Map")
      .def(init< unsigned , unsigned , double , unsigned ,
                 double , unsigned , unsigned , unsigned >())
      .def("height", & Map::height)
      .def("width", & Map::width)
      .def("matrix", static_cast< sharedMatrix(Map::*)() >(& Map::matrix))
   ;

   class_< Matrix, sharedMatrix, boost::noncopyable >("Matrix", init< unsigned, unsigned >())
      .def("indexFromPosition", & Matrix::indexFromPosition)
      .def("positionFromIndex", & Matrix::positionFromIndex)
      .def("height", & Matrix::height)
      .def("width", & Matrix::width)
      .def("size", & Matrix::size)
      .def("pixelAtIndex",
           static_cast< sharedPixel(Matrix:: *)(unsigned) >(& Matrix::pixelAtIndex))
      .def("pixelAtPosition",
           static_cast< sharedPixel(Matrix:: *)(unsigned, unsigned) >
           (& Matrix::pixelAtPosition))
      .def("pixelsAroundIndex",
           static_cast< pixelList(Matrix:: *)(unsigned, unsigned) >
           (& Matrix::pixelsAroundIndex))
      .def("pixelsAroundPosition",
           static_cast< pixelList(Matrix:: *)(unsigned, unsigned, unsigned) >
           (& Matrix::pixelsAroundPosition))
   ;

   class_< Pixel, sharedPixel, boost::noncopyable >("Pixel", init< unsigned, bool >())
      .def("index", & Pixel::index)
      .add_property("height", get_heightPixel, set_heightPixel)
      .def("isBorder", & Pixel::isBorder)
      .def("isUnitsEmpty", & Pixel::isUnitsEmpty)
      .def("isUnitsUnique", & Pixel::isUnitsUnique)
      .def("nOfUnits", & Pixel::nOfUnits)
      .def("addUnit", & Pixel::addUnit)
      .def("removeUnit", & Pixel::removeUnit)
      .def("clearUnits", & Pixel::clearUnits)
      .def("units", static_cast< unitList(Pixel:: *)() >(& Pixel::units))
   ;

   class_< Unit, sharedUnit, boost::noncopyable >("Unit", init< unsigned >())
      .add_property("radius", get_radiusUnit, set_radiusUnit)
      .def("fieldOfView", & Unit::fieldOfView)
      .def("longevity", get_longevityUnit)
      .def("fertility", get_fertilityUnit)
      .def("belligerance", get_belligeranceUnit)
      .def("addPixel", & Unit::addPixel)
      .def("removePixel", & Unit::removePixel)
      .def("clearPixels", & Unit::clearPixels)
      .def("centralPixel", static_cast< void(Unit::*)(sharedPixel) >(& Unit::centralPixel))
      .def("centralPixel", static_cast< sharedPixel(Unit::*)() >(& Unit::centralPixel))
      .def("pixels", static_cast< pixelList(Unit::*)() >(& Unit::pixels))
   ;
}

#endif /* fourFs_CLASSES_HPP_ */
