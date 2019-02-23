#include "GeometryNode.hpp"
#include "Helpers.hpp"

bool GeometryNode::intersectImpl(const Ray &r, glm::vec4 &p, glm::vec4 &normal) const {
  float t;
  bool res = prim->intersect(r, t, normal);
  p = r.pointAt(t - constants::EPSILON);
  return res;
}
