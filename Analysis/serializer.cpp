/*
 * serializer.cpp
 *
 *  Created on: Apr 8, 2013
 *      Author: Enoah Netzach
 */

#include "serializer.h"

#include <fstream>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/lexical_cast.hpp>

#include "map_serialization.hpp"
#include "matrix_serialization.hpp"
#include "pixel_serialization.hpp"
#include "unit_serialization.hpp"

using namespace fourFs;
using namespace analysis;
using namespace logic;

Serializer::Serializer(const char * basePath)
   : m_basePath(basePath)
{
}

Serializer::~Serializer()
{
}

bool Serializer::save(const logic::Map & map) const
{
   bool retValue = false;

   std::string input = "";

   boost::filesystem::path filePath;

   while (true)
   {
      std::cout << "[Serializer] Insert file location (insert 'd' or a directory"
                   "for default name, 'q' to abort): " << std::flush;
      std::cin >> input;

      if (input == "q") break;

      if (input == "d") input = ".";

      filePath = input;

      if (boost::filesystem::is_regular_file(filePath))
      {
         std::cout << "[Serializer] File " << filePath << " does exists, overwrite? (y/n)" << std::flush;
         std::cin >> input;

         if (input == "n") continue;
      }
      else if (boost::filesystem::is_directory(filePath))
      {
         unsigned i = 0;
         boost::filesystem::path fileTest;

         do
         {
            fileTest = filePath;
            fileTest += "/fourFsSave_";
            fileTest += boost::lexical_cast< std::string >(i);
            fileTest += ".4fs";

            i++;
         } while (boost::filesystem::exists(fileTest));

         filePath = fileTest;
      }
      else
      {
         std::cout << std::boolalpha << boost::filesystem::is_directory(filePath) << std::endl;
         std::cout << "[Serializer] File " << filePath << " exists but cannot be modified." << std::endl;

         continue;
      }

      std::cerr << "OK " << filePath << std::endl;

      // save
      std::ofstream ofs(filePath.string().c_str());
      boost::archive::text_oarchive oa(ofs);
      // write class instance to archive
      oa << map;

      if (ofs.good()) retValue = true;
      std::cout << "[Serializer] File saved: " << filePath << "." << std::endl;

      ofs.close();

      break;
   }

   return retValue;
}

logic::Map Serializer::load() const
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
         std::cout << "[Serializer] File " << filePath << " does not exists or is not a regular file." << std::flush;
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
