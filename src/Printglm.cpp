#include "Printglm.hpp"

ostream &
operator<<(ostream &os, const glm::dvec3 &d)
{
  os << to_string(d);
  return os;
}

ostream &
operator<<(ostream &os, const glm::dvec4 &d)
{
  os << to_string(d);
  return os;
}
