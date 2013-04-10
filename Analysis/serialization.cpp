/*
 * serialization.cpp
 *
 *  Created on: Apr 10, 2013
 *      Author: Enoah Netzach
 */

#include "serialization.h"

#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/utility.hpp>

#include "../utilities.hpp"
#include "map_serialization.hpp"
#include "matrix_serialization.hpp"
#include "pixel_serialization.hpp"
#include "unit_serialization.hpp"

using namespace fourFs;

bool fourFs::analysis::serialization::save(const logic::Map & map)
{
   bool retValue = false;

   std::string input;
   std::cout << "[Serializer] Save file? (y/n)" << std::flush;
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

      // save
      std::ofstream ofs(filePath.string().c_str());
      boost::archive::text_oarchive oa(ofs);
      // write class instance to archive
      oa << map;

      if (boost::filesystem::is_regular_file(filePath)) retValue = true;
      std::cout << "[Serializer] File saved: " << filePath << "." << std::endl;

      ofs.close();
   }

   return retValue;
}

logic::Map fourFs::analysis::serialization::load()
{
   logic::Map map;

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
                   << " does not exists or is not a regular file." << std::flush;
         continue;
      }

      // load
      std::ifstream ifs(filePath.string().c_str());
      boost::archive::text_iarchive ia(ifs);
      // read class state from archive
      ia >> map;

      std::cout << "[Serializer] File load: " << filePath << "." << std::endl;

      break;
   }

   return map;
}
