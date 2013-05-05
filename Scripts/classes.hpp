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
#include "../Logic/swarm.h"
#include "../Logic/unit.h"
#include "wrappers.hpp"

// Show the type without parenthesis
#define REM(...) __VA_ARGS__
#define PAIR(x) REM x

#define GET_REF(className, type, function) \
   type get_ ## className ## _ ## function(className & c) \
   { \
      return c->function(); \
   }

#define SET_REF(className, type, function) \
   void set_ ## className ## _ ## function(className & c, type n) \
   { \
      c->function() = n; \
   }

#define GET_SET_REF(className, type, function) \
   GET_REF(className, type, function) \
   SET_REF(className, type, function)

#define SET_VAL(className, type, function) \
   void set_ ## className ## _ ## function(className & c, type n) \
   { \
      c->function(n); \
   }

#define CALL_METHOD(type) \
   type call_ ## type(type & c) { return c; }

#define OVERLOAD(className, method, returnType, args, ...) \
   static_cast< returnType(className:: *)(PAIR(args)) __VA_ARGS__ >(& className::method)

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

CALL_METHOD(sharedMap)
CALL_METHOD(sharedMatrix)
CALL_METHOD(sharedPixel)
CALL_METHOD(sharedUnit)
GET_SET_REF(sharedPixel, double, height)
GET_SET_REF(sharedUnit, unsigned, radius)
GET_REF(sharedUnit, double, longevity)
GET_REF(sharedUnit, double, fertility)
GET_REF(sharedUnit, double, belligerance)

BOOST_PYTHON_MODULE(fourFs)
{
   using namespace boost::python;

   // random generators
   def("randInt", randInt);
   def("randReal", randReal);
   def("rand01", rand01);

   EXPORT_STD_LIST(pixelList, "PixelList")
   EXPORT_STD_LIST(unitList, "UnitList")
   EXPORT_STD_MAP(unitMap, "UnitMap")

   EXPORT_STD_PAIR(Matrix::coordinates, "Pos")

   class_< sharedMap >("Map")
      .def("__call__", call_sharedMap, return_value_policy< return_by_value >())
      .def("height", & Map::height)
      .def("width", & Map::width)
      .def("matrix", OVERLOAD(Map, matrix, sharedMatrix, ()),
           return_value_policy< return_by_value >())
   ;

   class_< sharedMatrix >("Matrix")
      .def("__call__", call_sharedMap, return_value_policy< return_by_value >())
      .def("indexFromPosition", & Matrix::indexFromPosition)
      .def("positionFromIndex", & Matrix::positionFromIndex)
      .def("height", & Matrix::height)
      .def("width", & Matrix::width)
      .def("size", & Matrix::size)
      .def("pixelAtIndex", OVERLOAD(Matrix, pixelAtIndex, sharedPixel, (unsigned)),
           return_value_policy< return_by_value >())
      .def("pixelAtPosition",
           OVERLOAD(Matrix, pixelAtPosition, sharedPixel, (unsigned, unsigned)),
           return_value_policy< return_by_value >())
      .def("pixelsAroundIndex",
           OVERLOAD(Matrix, pixelsAroundIndex, pixelList, (unsigned, unsigned)))
      .def("pixelsAroundPosition",
           OVERLOAD(Matrix, pixelsAroundPosition, pixelList, (unsigned, unsigned, unsigned)))
   ;

   class_< sharedPixel >("Pixel")
      .def("__call__", call_sharedPixel, return_value_policy< return_by_value >())
      .def("index", & Pixel::index)
      .add_property("height", get_sharedPixel_height, set_sharedPixel_height)
      .def("isBorder", & Pixel::isBorder)
      .def("isUnitsEmpty", & Pixel::isUnitsEmpty)
      .def("isUnitsUnique", & Pixel::isUnitsUnique)
      .def("nOfUnits", & Pixel::nOfUnits)
      .def("addUnit", & Pixel::addUnit)
      .def("removeUnit", & Pixel::removeUnit)
      .def("clearUnits", & Pixel::clearUnits)
      .def("units", & Pixel::units)
   ;

   class_< sharedSwarm >("Swarm")
      .def("size", & Swarm::size)
      .def("empty", & Swarm::empty)
      .def("addUnit", & Swarm::addUnit)
      .def("removeUnit", & Swarm::removeUnit)
      .def("clearUnits", & Swarm::clearUnits)
      .def("unitFromId", OVERLOAD(Swarm, unitFromId, sharedUnit, (id_type)))
      .def("units", & Swarm::units)
   ;

   class_< sharedUnit >("Unit")
      .def("__call__", call_sharedUnit, return_value_policy< return_by_value >())
      .add_property("radius", get_sharedUnit_radius, set_sharedUnit_radius)
      .def("fieldOfView", & Unit::fieldOfView)
      .def("longevity", get_sharedUnit_longevity)
      .def("fertility", get_sharedUnit_fertility)
      .def("belligerance", get_sharedUnit_belligerance)
      .def("addPixel", & Unit::addPixel)
      .def("removePixel", & Unit::removePixel)
      .def("clearPixels", & Unit::clearPixels)
      .def("centralPixel", OVERLOAD(Unit, centralPixel, void, (index_type)))
      .def("centralPixel", OVERLOAD(Unit, centralPixel, index_type, (), const))
      .def("pixels", & Unit::pixels)
   ;
}

#endif /* fourFs_CLASSES_HPP_ */
