#ifndef NODE_HPP_
#define NODE_HPP_

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace node {
   typedef std::string ID;
   typedef std::string Name;
   typedef std::string Object;
}  // namespace node

struct Path {
   enum class Direction { West,
                          North,
                          East,
                          South };
   const Direction _direction;
   const node::ID _room_id;
   Path(Direction direction, node::ID id) :
       _direction(direction),
       _room_id(id) {}

   node::ID id() const { return _room_id; }
   std::string directionToString();
   static Direction stringToDirection(const std::string& dir);

   template <typename TPtr>
   bool isEqual(TPtr rhs) const { return _room_id == rhs->_room_id; }
   static std::shared_ptr<Path> createPath(Path::Direction direction, const node::ID& id);
};

struct Node {
   enum class State { NotVisited,
                      Visited };
   const node::ID _room_id;
   const node::Name _name;
   State _state;
   std::vector<node::Object> _objects;
   std::shared_ptr<std::vector<std::shared_ptr<Path>>> neighbours;
   std::shared_ptr<Node> pathParent;

   Node(const node::ID& id, const node::Name& name, const std::vector<node::Object>& objects = {});

   std::string toString() const { return _name; }
   node::ID id() const { return _room_id; }
   bool unvisited() { return _state == State::NotVisited; }
   void setVisited() { _state = State::Visited; }

   void addNeighbour(std::shared_ptr<Path> adjacent) { neighbours->push_back(adjacent); }
   void clearPath() {
      _state = State::NotVisited;
      pathParent = nullptr;
   }

   template <typename TPtr>
   bool isEqual(TPtr rhs) const { return _room_id == rhs->_room_id; }

   template <typename TPtr>
   bool operator==(TPtr rhs) const { return _room_id == rhs->_room_id; }

   std::vector<node::Object> seeObjects() { return _objects; }
   bool hasObject() const { return _objects.size() > 0; }
   bool hasObject(const node::Object& object);
   bool takeObject(const node::Object& object);

   template <typename TPtr>
   bool isAdjacent(TPtr node_or_path) {
      const auto iter = std::find_if(
         neighbours->begin(),
         neighbours->end(),
         [&](std::shared_ptr<Path> n) { return node_or_path->isEqual(n); });
      return iter != neighbours->end();
   }

   std::shared_ptr<Path> getAdjacent(node::ID id) {
      const auto iter = std::find_if(
         neighbours->begin(),
         neighbours->end(),
         [&](std::shared_ptr<Path> n) { return n->id() == id; });
      if (iter == neighbours->end())
         return {};
      return *iter;
   }
};

typedef std::shared_ptr<Node> Nodeptr;
typedef std::shared_ptr<Path> Pathptr;
typedef std::shared_ptr<std::vector<Pathptr>> Pathlist;
typedef std::shared_ptr<std::vector<Nodeptr>> Nodelist;
typedef std::vector<node::Object> Objectlist;
bool operator<(const Pathptr& lhs, const Pathptr& rhs);

#endif  // NODE_HPP_
