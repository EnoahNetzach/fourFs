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

#include <boost/preprocessor.hpp>
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
#define EAT(...)
// Retrieve the type
#define TYPEOF(x) DETAIL_TYPEOF(DETAIL_TYPEOF_PROBE x,)
#define DETAIL_TYPEOF(...) DETAIL_TYPEOF_HEAD(__VA_ARGS__)
#define DETAIL_TYPEOF_HEAD(x, ...) REM x
#define DETAIL_TYPEOF_PROBE(...) (__VA_ARGS__),
// Strip off the type
#define STRIP(x) EAT x
// Show the type without parenthesis
#define PAIR(x) REM x
#define DETAIL_DEFINE_ARGS_EACH(r, data, i, x) BOOST_PP_COMMA_IF(i) PAIR(x)
#define DETAIL_DEFINE_FORWARD_EACH(r, data, i, x) BOOST_PP_COMMA_IF(i) STRIP(x)
// Get args like (int a, int b)
#define DETAIL_DEFINE_ARGS(args) \
   BOOST_PP_SEQ_FOR_EACH_I(DETAIL_DEFINE_ARGS_EACH, data, BOOST_PP_VARIADIC_TO_SEQ args)
// Get args like (a, b)
#define DETAIL_DEFINE_FORWARD(args) \
   BOOST_PP_SEQ_FOR_EACH_I(DETAIL_DEFINE_FORWARD_EACH, data, BOOST_PP_VARIADIC_TO_SEQ args)

#define GET_VAL(className, function, type) \
   type get_ ## className ## _ ## function(className & c) \
   { \
      return c->function(); \
   }

#define SET_REF(className, function, type) \
   void set_ ## className ## _ ## function(className & c, type n) \
   { \
      c->function() = n; \
   }

#define GET_SET_REF(className, function, type) \
   GET_VAL(className, function, type) \
   SET_REF(className, function, type)

#define SET_VAL(className, function, type) \
   void set_ ## className ## _ ## function(className & c, type n) \
   { \
      c->function(n); \
   }

#define GET_SET_VAL(className, function, type) \
   GET_VAL(className, function, type) \
   SET_VAL(className, function, type)

#define GET_ARGS(className, function, type, args) \
   type className ## _ ## function(className & c, DETAIL_DEFINE_ARGS(args)) \
   { \
      return c->function(DETAIL_DEFINE_FORWARD(args)); \
   }

#define GET(className, function, type) \
   type className ## _ ## function(className & c) \
   { \
      return c->function(); \
   }

#define CALL_ARGS(className, function, args) \
   void className ## _ ## function(className & c, DETAIL_DEFINE_ARGS(args)) \
   { \
      c->function(DETAIL_DEFINE_FORWARD(args)); \
   }

#define CALL(className, function) \
   void className ## _ ## function(className & c) \
   { \
      c->function(); \
   }

#define CALL_METHOD(type) \
   type call_method_ ## type(type & c) { return c; }

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
GET(sharedMap, height, double)
GET(sharedMap, width, double)
GET_SET_REF(sharedMap, matrix, sharedMatrix)

CALL_METHOD(sharedMatrix)
GET_ARGS(sharedMatrix, indexFromPosition, index_type, ((unsigned)x, (unsigned)y))
GET_ARGS(sharedMatrix, positionFromIndex, Matrix::coordinates, ((index_type)index))
GET(sharedMatrix, height, unsigned)
GET(sharedMatrix, width, unsigned)
GET(sharedMatrix, size, unsigned)
GET_ARGS(sharedMatrix, pixelAtIndex, sharedPixel, ((index_type)index))
GET_ARGS(sharedMatrix, pixelAtPosition, sharedPixel, ((unsigned)x, (unsigned)y))
GET_ARGS(sharedMatrix, pixelsAroundIndex, pixelList, ((index_type)index, (unsigned)radius))
GET_ARGS(sharedMatrix, pixelsAroundPosition, pixelList, ((unsigned)x, (unsigned)y, (unsigned)radius))

CALL_METHOD(sharedPixel)
GET(sharedPixel, index, unsigned)
GET_SET_REF(sharedPixel, height, double)
GET(sharedPixel, isBorder, bool)
GET(sharedPixel, isUnitsEmpty, bool)
GET(sharedPixel, isUnitsUnique, bool)
GET(sharedPixel, nOfUnits, unsigned)
CALL_ARGS(sharedPixel, addUnit, ((id_type)id))
GET_ARGS(sharedPixel, removeUnit, bool, ((id_type)id))
CALL(sharedPixel, clearUnits)
GET_ARGS(sharedPixel, hasUnit, bool, ((id_type)id))
GET(sharedPixel, units, idList)

CALL_METHOD(sharedSwarm)
GET(sharedSwarm, size, unsigned)
GET(sharedSwarm, empty, bool)
GET_ARGS(sharedSwarm, addUnit, sharedUnit, ((unsigned)radius))
CALL_ARGS(sharedSwarm, removeUnit, ((id_type)id))
GET_ARGS(sharedSwarm, deleteUnits, indexList, ((unsigned)num))
GET(sharedSwarm, clearUnits, indexList)
GET_ARGS(sharedSwarm, unitFromId, sharedUnit, ((id_type)id))
GET(sharedSwarm, units, unitMap)

CALL_METHOD(sharedUnit)
GET(sharedUnit, id, id_type)
GET_SET_REF(sharedUnit, radius, unsigned)
GET(sharedUnit, fieldOfView, double)
GET(sharedUnit, longevity, double)
GET(sharedUnit, fertility, double)
GET(sharedUnit, belligerance, double)
CALL_ARGS(sharedUnit, addPixel, ((index_type)index))
GET_ARGS(sharedUnit, removePixel, bool, ((index_type)index))
CALL(sharedUnit, clearPixels)
GET_ARGS(sharedUnit, hasPixel, bool, ((index_type)index))
GET(sharedUnit, pixels, indexList)
GET_SET_VAL(sharedUnit, centralPixel, index_type)

BOOST_PYTHON_MODULE(fourFs)
{
   using namespace boost::python;

   // random generators
   def("randInt", randInt);
   def("randReal", randReal);
   def("rand01", rand01);

   EXPORT_STD_LIST(pixelList, "PixelList")
   EXPORT_STD_LIST(unitList, "UnitList")
   EXPORT_STD_LIST_OF_TYPE(unsigned, "UnsignedList")
   EXPORT_STD_MAP(unitMap, "UnitMap")

   EXPORT_STD_PAIR(Matrix::coordinates, "Pos")

   class_< sharedMap >("Map")
      .def("__call__", call_method_sharedMap, return_value_policy< return_by_value >())
      .add_property("height", sharedMap_height)
      .add_property("width", sharedMap_width)
      .add_property("matrix", get_sharedMap_matrix, set_sharedMap_matrix)
   ;

   class_< sharedMatrix >("Matrix")
      .def("__call__", call_method_sharedMatrix, return_value_policy< return_by_value >())
      .def("indexFromPosition", sharedMatrix_indexFromPosition)
      .def("positionFromIndex", sharedMatrix_positionFromIndex)
      .def("height", sharedMatrix_height)
      .def("width", sharedMatrix_width)
      .def("size", sharedMatrix_size)
      .def("pixelAtIndex", sharedMatrix_pixelAtIndex,
           return_value_policy< return_by_value >())
      .def("pixelAtPosition", sharedMatrix_pixelAtPosition,
           return_value_policy< return_by_value >())
      .def("pixelsAroundIndex", sharedMatrix_pixelsAroundIndex)
      .def("pixelsAroundPosition", sharedMatrix_pixelsAroundPosition)
   ;

   class_< sharedPixel >("Pixel")
      .def("__call__", call_method_sharedPixel, return_value_policy< return_by_value >())
      .def("index", sharedPixel_index)
      .add_property("height", get_sharedPixel_height, set_sharedPixel_height)
      .def("isBorder", sharedPixel_isBorder)
      .def("isUnitsEmpty", sharedPixel_isUnitsEmpty)
      .def("isUnitsUnique", sharedPixel_isUnitsUnique)
      .def("nOfUnits", sharedPixel_nOfUnits)
      .def("addUnit", sharedPixel_addUnit)
      .def("removeUnit", sharedPixel_removeUnit)
      .def("clearUnits", sharedPixel_clearUnits)
      .def("hasUnit", sharedPixel_hasUnit)
      .def("units", sharedPixel_units)
   ;

   class_< sharedSwarm >("Swarm")
      .def("__call__", call_method_sharedSwarm, return_value_policy< return_by_value >())
      .def("size", sharedSwarm_size)
      .def("empty", sharedSwarm_empty)
      .def("addUnit", sharedSwarm_addUnit)
      .def("removeUnit", sharedSwarm_removeUnit)
      .def("clearUnits", sharedSwarm_clearUnits)
      .def("unitFromId", sharedSwarm_unitFromId)
      .def("units", sharedSwarm_units)
   ;

   class_< sharedUnit >("Unit")
      .def("__call__", call_method_sharedUnit, return_value_policy< return_by_value >())
      .def("id", sharedUnit_id)
      .add_property("radius", get_sharedUnit_radius, set_sharedUnit_radius)
      .def("fieldOfView", sharedUnit_fieldOfView)
      .def("longevity", sharedUnit_longevity)
      .def("fertility", sharedUnit_fertility)
      .def("belligerance", sharedUnit_belligerance)
      .def("addPixel", sharedUnit_addPixel)
      .def("removePixel", sharedUnit_removePixel)
      .def("clearPixels", sharedUnit_clearPixels)
      .add_property("centralPixel", get_sharedUnit_centralPixel, set_sharedUnit_centralPixel)
      .def("pixels", sharedUnit_pixels)
   ;
}

#endif /* fourFs_CLASSES_HPP_ */
