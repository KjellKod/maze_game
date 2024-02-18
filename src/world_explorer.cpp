#include "world_explorer.hpp"
#include "string_utility.hpp"

#include <stack>
#include <cassert>
#include <algorithm>

namespace
{
  const std::string c_text_in_room = {"In the "};
  const std::string c_text_walking = {"I go "};
  const std::string c_text_take = {"I collect the "};
  const std::string c_search_failure{"No more rooms to search. I cannot find all items"};

  typedef std::stack<Nodeptr> PathTravelled;


  Objectlist foundItems(Nodeptr room, const Objectlist& any_of_these){
     if(false == room->hasObject()) return {};
     Objectlist found;
     for(auto& object: any_of_these) {
       if(room->hasObject(object)) found.push_back(object);
     }
   return found;
 }

  // IMPORTANT: If duplicates, then these will ALL be removed
  void removeFoundObject(const node::Object& remove_found, Objectlist& objects_to_find) {
    auto size = objects_to_find.size();
    objects_to_find.erase( std::remove(objects_to_find.begin(), objects_to_find.end(), remove_found));
    assert(objects_to_find.size() < size);
  }


  void retrieveObjects(Nodeptr current, std::stringstream& story, Objectlist& objects_to_find) {
    const auto objects_in_room = foundItems(current, objects_to_find);
    if(!objects_in_room.empty()) {
      for(auto object : objects_in_room) {
        story << c_text_take << object << std::endl;
        removeFoundObject(object, objects_to_find);
      }
    }
  }

  Pathlist getUnvisited(Graph& g, Nodeptr n) {
     Pathlist unvisited_nodes(new std::vector<Pathptr>());

     for (auto adjacent : *(n->neighbours)) {
       auto next = g.findNode(adjacent->id());
        if (next->unvisited())
           unvisited_nodes->push_back(adjacent);
     }

     std::sort(unvisited_nodes->begin(), unvisited_nodes->end());
     return unvisited_nodes;
  }


  Nodeptr walkToNext(Graph& graph, PathTravelled& path, std::stringstream& story, Nodeptr current){
    auto unvisited = getUnvisited(graph, current);
    Pathptr next_path = nullptr;

    if(!unvisited->empty()) {
      next_path = unvisited->front();
      path.push(current);
    }
    else {
      if(path.empty()) return nullptr;

      auto old_node = path.top();
      path.pop();
      next_path =  current->getAdjacent(old_node->id());
    }

      story << c_text_walking << next_path->directionToString() << std::endl;
      Nodeptr next_current = graph.findNode(next_path->id());
      next_current->setVisited();
      story << c_text_in_room << next_current->toString() << std::endl;
      return next_current;
  }
} // anonymous








WorldExplorer::WorldExplorer(Graph& graph, Nodeptr start_room)
  : _graph(graph),
    _start_room(start_room)
{ }



std::string WorldExplorer::exploreToFindObjects(Objectlist& objects_to_find) {
  using namespace std;
  _story.str("");
  _graph.clearFoundPath();

  PathTravelled  path_travelled;
  _story << c_text_in_room << _start_room->toString() << endl;
  _start_room->setVisited();

  Nodeptr current = _start_room; //path_travelled.top();
  while(current && !objects_to_find.empty()) {
    retrieveObjects(current, _story, objects_to_find);

  if(!objects_to_find.empty())
    current = walkToNext(_graph, path_travelled, _story, current);
  }

  return _story.str();
}
