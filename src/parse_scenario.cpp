#include <iostream>
#include <sstream>
#include <fstream>
#include "parse_scenario.hpp"
#include "string_utility.hpp"


namespace parse_scenario
{
Content extractContentFromRaw(const std::string& raw) {
  using namespace std;
  using namespace string_utility;

  Content content;
  string line;
  stringstream stream(raw);
  if(getline(stream, line))
    content._room_id = trim(line);

  while(getline(stream, line)) {
    line = trim(line);
    if(!line.empty())
      content._to_find.push_back(line);
  }
  return content;
}


std::string readFile(const std::string& filename){
  using namespace std;
  ifstream file(filename);
  if (!file)
    return {""};

  file.seekg(0, ios::end);
  auto size = file.tellg();
  file.seekg(0, ios::beg);

  vector<char> buffer(size);
  file.read(&buffer[0], size);

  stringstream content;
  content.rdbuf()->pubsetbuf(&buffer[0], size);

  return content.str();
}

Content loadScenario(const std::string& filename) {
  auto raw = readFile(filename);
  return extractContentFromRaw(raw);
}

} // parse_scenario
