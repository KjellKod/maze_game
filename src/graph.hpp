#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <map>
#include <string>
#include <vector>
#include "node.hpp"

class Graph
{
   std::vector<Nodeptr>   _nodes;

public:
  Graph(){}
  ~Graph(){}
  void addNode(Nodeptr n);
  Nodeptr findNode(Nodeptr n);
  Nodeptr findNode(const node::ID& id);
  Nodeptr findNodeFromObject(node::Object object);

  Pathlist getAdjacent(Nodeptr n);
  bool areAdjacent(Nodeptr n1, Nodeptr n2);

  void printGraph();
  void clearFoundPath();
};

#endif // GRAPH_HPP
