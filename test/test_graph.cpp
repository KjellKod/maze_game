#include <gtest/gtest.h>
#include <memory>
#include <vector>

#include "graph.hpp"
#include "node.hpp"

using namespace std;

namespace {
   enum class HasItems { WithItems,
                         NoItems };

   Nodeptr createNode(const node::ID& id, const node::Name& name, HasItems has_items = HasItems::NoItems) {
      vector<node::Object> objects{{"Knife"}, {"Table"}};
      if (has_items == HasItems::WithItems)
         return std::make_shared<Node>(id, name, objects);

      return std::make_shared<Node>(id, name);
   }

   Pathptr createPath(Path::Direction direction, const node::ID& id) {
      return std::make_shared<Path>(direction, id);
   }

}  // namespace

TEST(Graph, Initial) {
   Graph graph;
   auto node = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   ASSERT_TRUE(nullptr == graph.findNode(node));
   graph.addNode(node);
   ASSERT_TRUE(nullptr != graph.findNode(node));
   ASSERT_TRUE(nullptr != graph.findNode(node::ID{"-kitchen-"}));
}

TEST(Graph, getAdjacent) {
   Graph graph;
   auto node_start = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   auto node_1 = createNode({"-bathroom-"}, {"Blue Bathroom"});
   auto node_2 = createNode({"-hallway-"}, {"Hallway"});

   node_start->addNeighbour(createPath(Path::Direction::West, {"-bathroom-"}));
   node_1->addNeighbour(createPath(Path::Direction::East, {"-kitchen-"}));

   node_start->addNeighbour(createPath(Path::Direction::North, {"-hallway-"}));
   node_2->addNeighbour(createPath(Path::Direction::South, {"-kitchen-"}));

   graph.addNode(node_start);
   graph.addNode(node_1);
   graph.addNode(node_2);

   ASSERT_TRUE(graph.areAdjacent(node_start, node_1));
   ASSERT_TRUE(graph.areAdjacent(node_start, node_2));
   ASSERT_FALSE(graph.areAdjacent(node_1, node_2));
}

TEST(Graph, printGraph) {
   Graph graph;
   auto node_start = createNode({"-kitchen-"}, {"Fancy Kitchen"}, HasItems::WithItems);
   auto node_1 = createNode({"-bathroom-"}, {"Blue Bathroom"});
   auto node_2 = createNode({"-hallway-"}, {"Hallway"});

   node_start->addNeighbour(createPath(Path::Direction::West, {"-bathroom-"}));
   node_start->addNeighbour(createPath(Path::Direction::North, {"-hallway-"}));

   node_1->addNeighbour(createPath(Path::Direction::East, {"-kitchen-"}));
   node_2->addNeighbour(createPath(Path::Direction::South, {"-kitchen-"}));

   graph.addNode(node_start);
   graph.addNode(node_1);
   graph.addNode(node_2);

   graph.printGraph();
}
