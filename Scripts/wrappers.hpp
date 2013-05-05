/*
 * wrappers.hpp
 *
 *  Created on: May 2, 2013
 *      Author: Enoah Netzach
 */

#ifndef fourFs_WRAPPERS_HPP_
#define fourFs_WRAPPERS_HPP_

#include <python2.7/Python.h>

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

//#define EXPORT_STD_PAIR_OF_TYPE(type1, type2, typeName) EXPORT_STD_PAIR(std::pair< type1, type2 >, typeName)

template< class T >
struct mapwrap
{
   typedef T map_type;
   typedef typename map_type::key_type key_type;
   typedef typename map_type::mapped_type mapped_type;
   typedef typename map_type::value_type value_type;
   typedef typename map_type::iterator iter_type;

   static mapped_type get(map_type & x, const key_type & v)
   {
      if (x.count(v) != 0)
      {
         return x.at(v);
      }
      else
      {
         PyErr_SetString(PyExc_IndexError, "Index out of range");
         boost::python::throw_error_already_set();
      }
   }

   static void set(map_type & x, const key_type & v, mapped_type & m)
   {
      if (x.count(v) == 0)
      {
         x.insert(std::make_pair(v, m));
      }
      else
      {
         PyErr_SetString(PyExc_IndexError, "Value already set");
         boost::python::throw_error_already_set();
      }
   }

   static void del(map_type & x, const key_type & v)
   {
      if (x.count(v) != 0)
      {
         x.erase(v);
      }
      else
      {
         PyErr_SetString(PyExc_IndexError, "Index out of range");
         boost::python::throw_error_already_set();
      }
   }
};

#define EXPORT_STD_MAP(type, typeName) \
   EXPORT_STD_PAIR(type::value_type, typeName "_pair") \
   boost::python::class_< type >(typeName) \
      .def("__len__", & type::size) \
      .def("clear", & type::clear) \
      .def("__getitem__", & mapwrap< type >::get) \
      .def("__setitem__", & mapwrap< type >::set, \
           boost::python::with_custodian_and_ward< 1, 2 >()) \
      .def("__delitem__", & mapwrap< type >::del) \
      .def("__contains__", & type::count) \
      .def("__iter__", iterator< type >()) \
   ;

//#define EXPORT_STD_MAP_OF_TYPE(type, typeName) EXPORT_STD_MAP(std::map< keyType, mapType >, typeName)

#endif /* fourFs_WRAPPERS_HPP_ */
