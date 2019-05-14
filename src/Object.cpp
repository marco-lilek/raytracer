#include "Object.hpp"

std::ostream& operator<<(std::ostream& o, const Object& b) {
  o << "[" << b.type() << " ";
  b.dump(o);
  o << "]";
  return o;
}

