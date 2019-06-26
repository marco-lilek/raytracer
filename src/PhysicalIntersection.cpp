#include "PhysicalIntersection.hpp"
#include "PhysicalNode.hpp"

std::ostream& PhysicalIntersection::dump(std::ostream& o) const {
  // TODO some convention for printing null objs
  if (hitNode != nullptr) {
    o << "hitNode.name " << hitNode->name;
  }
  if (geometry != nullptr) {
    o << " geometry " << *geometry;
  }

  return o;
}
