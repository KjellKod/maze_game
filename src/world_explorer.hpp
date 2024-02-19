#ifndef WORLD_EXPLORER_HPP
#define WORLD_EXPLORER_HPP

#include <sstream>
#include <string>
#include <vector>
#include "graph.hpp"
#include "node.hpp"

//The WorldExplorer is of the adventure type that explores and finds lost artifacts
//For some unexplained reason the explorer must always start exploring from ONE given location
class WorldExplorer {
   Graph& _graph;
   Nodeptr _start_room;
   std::stringstream _story;

  public:
   WorldExplorer(Graph& graph, Nodeptr start_room);
   virtual ~WorldExplorer() {}

   std::string exploreToFindObjects(Objectlist& to_find);
};

#endif
