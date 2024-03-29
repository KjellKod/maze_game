#ifndef PARSE_SCENARIO_HPP_
#define PARSE_SCENARIO_HPP_

#include <string>
#include <vector>

namespace parse_scenario {
   struct Content {
      std::string _room_id;
      std::vector<std::string> _to_find;
   };

   Content extractContentFromRaw(const std::string& raw);
   std::string readFile(const std::string& file);

   Content loadScenario(const std::string& file);
}  // namespace parse_scenario

#endif
