#include "parse_scenario.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include "string_utility.hpp"

namespace parse_scenario {
   Content extractContentFromRaw(const std::string& raw) {
      using namespace std;
      using namespace string_utility;

      Content content;
      string line;
      stringstream stream(raw);
      if (getline(stream, line))
         content._room_id = trim(line);

      while (getline(stream, line)) {
         line = trim(line);
         if (!line.empty())
            content._to_find.push_back(line);
      }
      return content;
   }

   std::string readFile(const std::string& filename) {
      std::filesystem::path filepath{filename};
      if (!std::filesystem::exists(filepath)) {
         std::cerr << "Could not open file: " << filename << std::endl;
         return {};
      }

      std::ifstream file(filepath, std::ios::binary);
      if (!file) {
         std::cerr << "Could not open file: " << filename << std::endl;
         return {};
      }

      std::string content{std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
      return content;
   }

   Content loadScenario(const std::string& filename) {
      auto raw = readFile(filename);
      return extractContentFromRaw(raw);
   }

}  // namespace parse_scenario
