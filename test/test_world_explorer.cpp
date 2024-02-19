
#include <gtest/gtest.h>
#include <memory>

#include "graph.hpp"
#include "node.hpp"
#include "parse_map.hpp"
#include "parse_scenario.hpp"
#include "string_utility.hpp"
#include "world_explorer.hpp"

using namespace std;

namespace {
   enum class HasItems { WithItems,
                         NoItems };
   const Objectlist objects{{"knife"}, {"table cloth"}};

   Nodeptr createNode(const node::ID& id, const node::Name& name, HasItems has_items = HasItems::NoItems) {
      if (HasItems::WithItems == has_items)
         return std::make_shared<Node>(id, name, objects);

      return std::make_shared<Node>(id, name);
   }
}  // namespace

TEST(WorldExplorer, NothingToFind) {
   Graph g;
   auto node_start = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   auto node_1 = createNode({"-bathroom-"}, {"Blue Bathroom"});
   g.addNode(node_start);
   g.addNode(node_1);
   node_start->addNeighbour(Path::createPath(Path::Direction::North, node_1->id()));
   node_1->addNeighbour(Path::createPath(Path::Direction::South, node_start->id()));

   WorldExplorer world_explorer{g, node_start};
   Objectlist empty;
   auto walk_story = world_explorer.exploreToFindObjects(empty);
   ASSERT_STREQ(string_utility::trim(walk_story, " \n \t").c_str(), "In the Fancy Kitchen");
}

TEST(WorldExplorer, AllObjectsAreInTheFirstRoom) {
   Graph g;
   auto node_start = createNode({"-kitchen-"}, {"Fancy Kitchen"}, HasItems::WithItems);
   auto node_1 = createNode({"-bathroom-"}, {"Blue Bathroom"});
   g.addNode(node_start);
   g.addNode(node_1);
   node_start->addNeighbour(Path::createPath(Path::Direction::North, node_1->id()));
   node_1->addNeighbour(Path::createPath(Path::Direction::South, node_start->id()));

   WorldExplorer world_explorer{g, node_start};
   Objectlist to_find(objects);
   auto walk_story = world_explorer.exploreToFindObjects(to_find);
   ASSERT_TRUE(walk_story.empty() == false);
   std::stringstream story;
   story << "In the Fancy Kitchen" << endl;
   story << "I collect the knife" << endl;
   story << "I collect the table cloth" << endl;
   ASSERT_STREQ(walk_story.c_str(), story.str().c_str());
   ASSERT_TRUE(to_find.empty());
}

TEST(WorldExplorer, AllObjectsAreInTheSecondRoom) {
   Graph g;
   auto node_start = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   auto node_1 = createNode({"-bathroom-"}, {"Blue Bathroom"}, HasItems::WithItems);
   g.addNode(node_start);
   g.addNode(node_1);
   node_start->addNeighbour(Path::createPath(Path::Direction::North, node_1->id()));
   node_1->addNeighbour(Path::createPath(Path::Direction::South, node_start->id()));

   WorldExplorer world_explorer{g, node_start};
   Objectlist to_find(objects);
   auto walk_story = world_explorer.exploreToFindObjects(to_find);
   ASSERT_TRUE(walk_story.empty() == false);
   std::stringstream story;
   story << "In the Fancy Kitchen" << endl;
   story << "I go north" << endl;
   story << "In the Blue Bathroom" << endl;
   story << "I collect the knife" << endl;
   story << "I collect the table cloth" << endl;
   ASSERT_STREQ(walk_story.c_str(), story.str().c_str());
}

TEST(WorldExplorer, AllObjectsAreInTheThirdRoom) {
   Graph g;
   auto node_start = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   auto node_1 = createNode({"-garage-"}, {"Garage"});
   auto node_2 = createNode({"-bathroom-"}, {"Blue Bathroom"}, HasItems::WithItems);
   g.addNode(node_start);
   g.addNode(node_1);
   g.addNode(node_2);
   node_start->addNeighbour(Path::createPath(Path::Direction::North, node_1->id()));
   node_1->addNeighbour(Path::createPath(Path::Direction::South, node_start->id()));

   node_1->addNeighbour(Path::createPath(Path::Direction::North, node_2->id()));
   node_2->addNeighbour(Path::createPath(Path::Direction::South, node_1->id()));

   WorldExplorer world_explorer{g, node_start};
   Objectlist to_find(objects);
   auto walk_story = world_explorer.exploreToFindObjects(to_find);
   ASSERT_TRUE(walk_story.empty() == false);
   std::stringstream story;
   story << "In the Fancy Kitchen" << endl;
   story << "I go north" << endl;
   story << "In the Garage" << endl;
   story << "I go north" << endl;
   story << "In the Blue Bathroom" << endl;
   story << "I collect the knife" << endl;
   story << "I collect the table cloth" << endl;
   ASSERT_STREQ(walk_story.c_str(), story.str().c_str());
}

TEST(WorldExplorer, OneObjectMissingFromTheThirdRoom) {
   Graph g;
   auto node_start = createNode({"-kitchen-"}, {"Fancy Kitchen"});
   auto node_1 = createNode({"-garage-"}, {"Garage"});
   auto node_2 = createNode({"-bathroom-"}, {"Blue Bathroom"}, HasItems::WithItems);
   g.addNode(node_start);
   g.addNode(node_1);
   g.addNode(node_2);
   node_start->addNeighbour(Path::createPath(Path::Direction::North, node_1->id()));
   node_1->addNeighbour(Path::createPath(Path::Direction::South, node_start->id()));

   node_1->addNeighbour(Path::createPath(Path::Direction::North, node_2->id()));
   node_2->addNeighbour(Path::createPath(Path::Direction::South, node_1->id()));

   WorldExplorer world_explorer{g, node_start};
   Objectlist objects_to_find(objects);
   objects_to_find.push_back("NoneExistantObject");
   auto walk_story = world_explorer.exploreToFindObjects(objects_to_find);
   ASSERT_TRUE(walk_story.empty() == false);
   std::stringstream story;
   story << "In the Fancy Kitchen" << endl;
   story << "I go north" << endl;
   story << "In the Garage" << endl;
   story << "I go north" << endl;
   story << "In the Blue Bathroom" << endl;
   story << "I collect the knife" << endl;
   story << "I collect the table cloth" << endl;
   story << "I go south" << endl;
   story << "In the Garage" << endl;
   story << "I go south" << endl;
   story << "In the Fancy Kitchen" << endl;
   ASSERT_STREQ(walk_story.c_str(), story.str().c_str());
   ASSERT_TRUE(objects_to_find.size() == size_t(1));
   ASSERT_STREQ(objects_to_find[0].c_str(), "NoneExistantObject");
}

namespace {
   std::string doc_map{"../configuration/map_from_docs.xml"};
   std::string doc_scenario{"../configuration/scenario_from_docs.txt"};
   //std::string doc_map{"../configuration/map.xml"};
   //std::string doc_scenario{"../configuration/scenario_1.txt"};
}  // namespace
TEST(WorldExplorer__Real, Small_Scenario_From_Docs____ExpectingNOExceptions) {
   try {
      auto graph = parse_map::loadGame(doc_map);
      auto scenario = parse_scenario::loadScenario(doc_scenario);
      auto start_room = graph.findNode(scenario._room_id);
      WorldExplorer world_explorer(graph, start_room);
      auto walk_story = world_explorer.exploreToFindObjects(scenario._to_find);
      //cout  << walk_story << endl;
      ASSERT_TRUE(true);
   } catch (std::exception e) {
      std::cerr << "The game encountered an xml parsing error: " << e.what() << std::endl;
      ASSERT_FALSE(true);
   }
}
