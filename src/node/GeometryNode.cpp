#include "GeometryNode.hpp"

bool GeometryNode::intersect(const Ray &r, float &t, glm::vec4 &normal) const {
  return p->intersect(r, t, normal);
}
