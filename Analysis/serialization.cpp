/*
 * serialization.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: Enoah Netzach
 */

#include "serialization.h"

#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility.hpp>

#include "map_serialization.hpp"
#include "matrix_serialization.hpp"
#include "pixel_serialization.hpp"
#include "unit_serialization.hpp"

namespace boost {
namespace serialization {

template< class Archive, typename Pointed >
inline void serialize(Archive & ar, boost::weak_ptr< Pointed > wp, unsigned v)
{
   boost::shared_ptr< Pointed > sp = wp.lock();
   ar & sp;
}

} /* namespace serialization */
} /* namespace boost */

using namespace fourFs;

bool fourFs::analysis::serialization::save(logic::sharedConstMap map)
{
   bool retValue = false;

   std::string input;
   std::cout << "[Serializer] Save file? (y/n) " << std::flush;
   std::cin >> input;

   if (input == "y")
   {
      boost::filesystem::path filePath;
      unsigned i = 0;
      do
      {
         filePath = "./fourFsSave_";
         filePath += boost::lexical_cast< std::string >(i);
         filePath += ".4fs";

         i++;
      } while (boost::filesystem::exists(filePath));

      // compress & save
      std::ofstream ofs(filePath.string().c_str());
      boost::iostreams::filtering_ostream f;
      f.push(boost::iostreams::zlib_compressor());
      f.push(ofs);
      boost::archive::binary_oarchive oa(f);
      // write class instance to archive
      oa << map;
      f.flush();

      if (boost::filesystem::is_regular_file(filePath)) retValue = true;
      std::cout << "[Serializer] File saved: " << filePath << "." << std::endl;

      ofs.close();
   }

   return retValue;
}

void analysis::serialization::load(logic::sharedMap map)
{
   std::string input = "";

   boost::filesystem::path filePath;

   while (true)
   {
      std::cout << "[Serializer] Insert file location (q to abort): " << std::flush;
      std::cin >> input;

      if (input == "q") break;

      filePath = input;

      if (! boost::filesystem::is_regular_file(filePath))
      {
         std::cout << "[Serializer] File " << filePath
                   << " does not exists or is not a regular file." << std::endl;
         continue;
      }

      // decompress & load
      std::ifstream ifs(filePath.string().c_str());
      boost::iostreams::filtering_istream f;
      f.push(boost::iostreams::zlib_decompressor());
      f.push(ifs);
      boost::archive::binary_iarchive ia(f);
      // read class state from archive
      try
      {
         ia >> map;

         std::cout << "[Serializer] File load: " << filePath << "." << std::endl;
      }
      catch (...)
      {
         std::cout << "[Serializer] File " << filePath << " not load, some error occurred." << std::endl;
      }

      break;
   }
}
