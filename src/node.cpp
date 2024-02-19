#include "node.hpp"
#include <algorithm>
#include <cassert>
#include <exception>
#include <map>
#include "string_utility.hpp"

std::shared_ptr<Path> Path::createPath(Path::Direction direction, const node::ID& id) {
   return std::make_shared<Path>(direction, id);
}

bool operator<(const Pathptr& lhs, const Pathptr& rhs) {
   return (static_cast<int>(lhs->_direction) < static_cast<int>(rhs->_direction));
}

namespace {
   std::map<Path::Direction, std::string> map_directions{{Path::Direction::East, "east"},
                                                         {Path::Direction::North, "north"},
                                                         {Path::Direction::South, "south"},
                                                         {Path::Direction::West, "west"}};

   struct IllegalDirectionException : public std::exception {
      std::string direction;
      explicit IllegalDirectionException(std::string dir) :
          direction(dir) {}

      virtual const char* what() const throw() {
         return direction.c_str();
      }
   };
}  // namespace

std::string Path::directionToString() {
   return map_directions[_direction];
}

Path::Direction Path::stringToDirection(const std::string& dir) {
   const Direction dummy = Direction::East;
   for (auto& pair : map_directions) {
      if (pair.second == dir)
         return pair.first;
   }

   throw IllegalDirectionException(dir);
   return dummy;
}

Node::Node(const node::ID& id, const node::Name& name, const std::vector<node::Object>& objects) :
    _room_id(string_utility::trim(id)),
    _name(string_utility::trim(name)),
    _state(State::NotVisited),
    _objects(objects),
    neighbours(new std::vector<std::shared_ptr<Path>>()),
    pathParent(nullptr) {}

bool Node::hasObject(const node::Object& object) {
   using namespace node;
   Object fixed_object = string_utility::tolower(object);
   auto found = find_if(_objects.begin(),
                        _objects.end(),
                        [&](node::Object& o) { return string_utility::tolower(o) == fixed_object; });
   return found != _objects.end();
}

bool Node::takeObject(const node::Object& object) {
   node::Object o;
   if (!hasObject(object))
      return false;
   size_t size = _objects.size();
   // BUG? here we remove ALL instances of the object. What if we only want to remove one?
   _objects.erase(std::remove(_objects.begin(), _objects.end(), object));
   assert(_objects.size() < size);
   return true;
}
