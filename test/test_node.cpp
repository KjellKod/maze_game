#include <gtest/gtest.h>
#include "node.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

namespace {
   Nodeptr createNode(const node::ID& id, const node::Name& name) {
      vector<node::Object> objects{{"Knife"}, {"Table"}};
      return std::make_shared<Node>(id, name, objects);
   }
}  // namespace

TEST(Node, Creation) {
   auto node = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   ASSERT_STREQ(node->id().c_str(), "-kitchen-");
   ASSERT_STREQ(node->toString().c_str(), "Fancy Kitchen");
   ASSERT_TRUE(node->unvisited());
   node->setVisited();
   ASSERT_FALSE(node->unvisited());
}

TEST(Node, Visited) {
   auto node = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   ASSERT_TRUE(node->unvisited());
   node->setVisited();
   ASSERT_FALSE(node->unvisited());
}

TEST(Node, FindingObjects) {
   auto node = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   ASSERT_TRUE(node->hasObject({"Knife"}));
   ASSERT_TRUE(node->hasObject({"Table"}));

   ASSERT_TRUE(node->takeObject({"Knife"}));
   ASSERT_FALSE(node->hasObject({"Knife"}));

   ASSERT_TRUE(node->takeObject({"Table"}));
   ASSERT_FALSE(node->hasObject({"Table"}));
}

TEST(Node, isADjacent) {
   using namespace std;
   auto node = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   shared_ptr<Path> path1 = make_shared<Path>(Path::Direction::East, "-cave-");
   shared_ptr<Path> path2 = make_shared<Path>(Path::Direction::East, "-living-room-");
   ASSERT_FALSE(node->isAdjacent(path1));
   ASSERT_FALSE(node->isAdjacent(path2));

   node->addNeighbour(path1);
   ASSERT_TRUE(node->isAdjacent(path1));
   ASSERT_FALSE(node->isAdjacent(path2));

   auto node_2 = createNode({"-living-room-"}, {"Living Room"});
   node->addNeighbour(path2);
   ASSERT_TRUE(node->isAdjacent(path2));
   ASSERT_TRUE(node->isAdjacent(node_2));
}

TEST(Node, DirectionFromString__AllOK) {
   ASSERT_TRUE(Path::Direction::East == Path::stringToDirection("east"));
   ASSERT_TRUE(Path::Direction::North == Path::stringToDirection("north"));
   ASSERT_TRUE(Path::Direction::South == Path::stringToDirection("south"));
   ASSERT_TRUE(Path::Direction::West == Path::stringToDirection("west"));
}
