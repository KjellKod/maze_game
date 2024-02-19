#ifndef STRING_UTILITY_HPP
#define STRING_UTILITY_HPP

#include <string>

namespace string_utility {
   std::string trim(const std::string& str, const std::string& whitespace = " \t");
   std::string tolower(const std::string& data);
}  // namespace string_utility

#endif  // STRING_UTILITY_HPP
