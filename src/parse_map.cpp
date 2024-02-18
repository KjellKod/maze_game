#include <iostream>
#include <cassert>
#include <vector>
#include <exception>

#include "parse_map.hpp"
#include "pugixml.hpp"


namespace {
  struct IllegalXMLToken: public std::exception
  {
    std::string token;
    explicit IllegalXMLToken(std::string text): token(text){}

    virtual const char* what() const throw()
    {
      return token.c_str();
    }
  };

}
namespace parse_map {


std::vector<Pathptr> loadPaths(pugi::xml_node& xml_node) {
  std::vector<Pathptr> paths;
  std::string direction_id;

  direction_id = xml_node.attribute("north").value();
  if(!direction_id.empty()) paths.push_back(Path::createPath(Path::Direction::North, direction_id));

  direction_id = xml_node.attribute("south").value();
  if(!direction_id.empty()) paths.push_back(Path::createPath(Path::Direction::South, direction_id));

  direction_id = xml_node.attribute("east").value();
  if(!direction_id.empty()) paths.push_back(Path::createPath(Path::Direction::East, direction_id));

  direction_id = xml_node.attribute("west").value();
  if(!direction_id.empty()) paths.push_back(Path::createPath(Path::Direction::West, direction_id));

  return paths;
}


Nodeptr createNode(pugi::xml_node& xml_node) {
  using namespace std;

  std::string id = xml_node.attribute("id").value();
  if(id.empty()) throw IllegalXMLToken("Invalid ID");

  std::string name = xml_node.attribute("name").value();
  if(name.empty()) throw IllegalXMLToken("Invalid name");

  std::vector<Pathptr> paths = loadPaths(xml_node);
  Objectlist objects;

  for(auto an_object : xml_node.children()) {
    for (auto found : an_object.attributes())
    {
      objects.push_back(found.value());
    }
  }

  auto room = std::make_shared<Node>(id, name, objects);
  for(auto p : paths)
    room->addNeighbour(p);

  return room;
}



Graph loadGame(std::string path_to_map) {
  pugi::xml_document doc;
  // a little HARSH perpaps. A Better solution would be to throw
  assert(doc.load_file(path_to_map.c_str()));
  Graph graph;
  pugi::xml_node world_map = doc.child("map");
  for(auto room: world_map.children())
  {
    auto real_room = createNode(room);
    graph.addNode(real_room);
  }

  return graph;
}
}
