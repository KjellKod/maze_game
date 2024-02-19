#include <gtest/gtest.h>
#include <string>
#include <algorithm>
#include "parse_scenario.hpp"

TEST(DUMMY, HelloWorld)
{
  const char* str = "Hello World";
  ASSERT_STREQ(str, "Hello World");
}


namespace scenario_0
{
  std::string file_0{"../configuration/scenario_from_docs.txt"};
  std::string file_raw{"2\n"\
                             "Potted Plant\n"\
                             "Knife"};

  bool foundRoomID(const std::string& raw_contents, const std::string& roomID) {
      using namespace parse_scenario;
      Content content = extractContentFromRaw(file_raw);
      return content._room_id == roomID;
  }

  bool foundItem(const parse_scenario::Content& content, const std::string& item)
  {
    auto iter = std::find(content._to_find.begin(), content._to_find.end(), item);
    return iter != content._to_find.end();
  }
}



TEST(Scenario_0___Parse_FindFile, Expecting___RoomID)
{
  using namespace scenario_0;
  ASSERT_TRUE(foundRoomID(file_raw, {"2"}));
}

TEST(Scenario_0___Parse_FindFile, Expecting___Contents)
{
  using namespace parse_scenario;
  using namespace scenario_0;
  Content content = extractContentFromRaw(file_raw);

  ASSERT_TRUE(foundItem(content, {"Potted Plant"}));
  ASSERT_TRUE(foundItem(content, {"Knife"}));
  ASSERT_FALSE(foundItem(content, {"1 2 3 4 5"}));
}


TEST(Scenario_0___Read_From_File__then_Parsing, Expecting___AllContents_To_Be_Valid)
{
  using namespace parse_scenario;
  using namespace scenario_0;
  auto raw = readFile(file_0);
  std::cout <<"raw is: " << raw << std::endl;
  ASSERT_FALSE(raw.empty());
  Content content = extractContentFromRaw(raw);

  ASSERT_TRUE(foundItem(content, {"Potted Plant"}));
  ASSERT_TRUE(foundItem(content, {"Knife"}));
  ASSERT_FALSE(foundItem(content, {"1 2 3 4 5"}));
}

