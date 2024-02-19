#include <algorithm>
#include <iostream>

#include "graph.hpp"
#include "node.hpp"

#include <cassert>
using namespace std;

void Graph::addNode(Nodeptr n) {
   if (!findNode(n)) {
      n->clearPath();
      _nodes.push_back(n);
   }
}

Nodeptr Graph::findNode(Nodeptr node) {
   auto itr = std::find(_nodes.begin(), _nodes.end(), node);
   if (itr != _nodes.end())
      return *itr;
   return Nodeptr(nullptr);
}

Nodeptr Graph::findNode(const node::ID& id) {
   for (auto itr : _nodes) {
      if (itr->id() == id)
         return itr;
   }
   return Nodeptr(nullptr);
}

Nodeptr Graph::findNodeFromObject(node::Object object) {
   for (auto itr : _nodes) {
      if (itr->hasObject(object))
         return itr;
   }
   return Nodeptr(nullptr);
}

Pathlist Graph::getAdjacent(Nodeptr n) {
   Nodeptr n_found = findNode(n);
   if (n_found) {
      return n_found->neighbours;
   }
   return nullptr;
}

bool Graph::areAdjacent(Nodeptr n1, Nodeptr n2) {
   Nodeptr n_found1 = findNode(n1);
   Nodeptr n_found2 = findNode(n2);
   if (!n_found1 || !n_found2)
      return false;

   return n_found1->isAdjacent(n2);
}

void Graph::printGraph() {
   for (auto n : _nodes) {
      cout << "** Room " << n->toString();
      if (n->hasObject()) {
         cout << "\t\twith objects: ";
         for (const auto& o : n->seeObjects())
            cout << "\t[" << o << "]";
      }
      std::cout << "\n";
      for (auto adjacent : *(n->neighbours)) {
         if (adjacent) {
            auto next = findNode(adjacent->id());
            cout << "\t"
                 << " -->" << next->toString() << endl;
         }
      }
      std::cout << "\n\n";
   }
}

void Graph::clearFoundPath() {
   for (auto n : _nodes) {
      n->clearPath();
   }
}
