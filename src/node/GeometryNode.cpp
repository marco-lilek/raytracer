#include "GeometryNode.hpp"
#include "Helpers.hpp"
#include <iostream>
#include <loguru/loguru.hpp>

using namespace std;

const Material * GeometryNode::intersectImpl(const Ray &r, glm::dvec4 &p, glm::dvec4 &normal) const {
  float t;
  bool res = prim->intersect(r, t, normal);
  if (res) {
    p = Ray::pointAt(r, t - constants::EPSILON);
    DLOG_F(INFO, "hit %s %p", name.c_str(), (void*)&material);
    return material;
  }
  return nullptr;
}
