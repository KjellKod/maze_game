#include "string_utility.hpp"
#include <algorithm>

namespace string_utility {

   std::string trim(const std::string& str, const std::string& whitespace) {
      const auto& begin = str.find_first_not_of(whitespace);
      if (begin == std::string::npos)
         return {""};

      const auto& end = str.find_last_not_of(whitespace);
      const auto& range = end - begin + 1;

      return str.substr(begin, range);
   }

   std::string tolower(const std::string& raw) {
      std::string data{raw};
      std::transform(data.begin(), data.end(),
                     data.begin(), ::tolower);
      return data;
   }
}  // namespace string_utility
