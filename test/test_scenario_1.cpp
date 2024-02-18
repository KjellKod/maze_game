#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream>
#include "map.xml.impl"
#include "pugixml.hpp"
#include "parse_map.hpp"

namespace {
  std::string file_map_xml{"../configuration/map.xml"};
  std::string scenario_1_file{"../configuration/scenario_1.txt"};
}



TEST(DISABLED_FigureOut_XML, PrintOut_LogRhythm_map_xml_example)
{
  pugi::xml_document doc;
  //ASSERT_TRUE(doc.load_file(file_map_xml.c_str()));
  ASSERT_TRUE(doc.load_file(scenario_1::mapfile.c_str()) == pugi::status_ok);
  pugi::xml_node world_map = doc.child("map");
  for(auto room: world_map.children())
  {
    std::cout << "\nroom" << std::endl;
    for (auto attr : room.attributes())
    {
      std::cout << "    [" << attr.name() << "=" << attr.value() << "]";
    }
    for(auto an_object : room.children()) {
      std::cout << "\n\tObjects found:";
      for (auto found : an_object.attributes())
      {
        std::cout << " [" << found.name() << "=" << found.value() << "]";
      }
    }
    std::cout << std::endl;
  }
}









