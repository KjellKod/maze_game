#include <iostream>
#include <exception>
#include "parse_map.hpp"
#include "parse_scenario.hpp"
#include "world_explorer.hpp"

namespace {
  std::string file_map_xml{"../configuration/map.xml"};
  std::string scenario_1_file{"../configuration/scenario_1.txt"};
}


int main() {
  try {
   auto graph = parse_map::loadGame(file_map_xml);
   const auto scenario = parse_scenario::loadScenario(scenario_1_file);
   auto start_room = graph.findNode(scenario._room_id);
   Objectlist to_find(scenario._to_find);
   WorldExplorer world_explorer{graph, start_room};
   auto node_path = world_explorer.exploreToFindObjects(to_find);
   std::cout << node_path << std::endl;

   if(to_find.empty())
     std::cout << "All objects found" << std::endl;
   else {
     std::cout << "All objects were NOT found: ";
     for( const auto& object : to_find) std::cout << object << " ";
     std::cout << "\n";
   }
  }
  catch(std::exception e)
  {
    std::cerr << "The game encountered an xml parsing error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
