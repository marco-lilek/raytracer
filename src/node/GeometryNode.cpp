#include "GeometryNode.hpp"
#include "Constants.hpp"
#include <iostream>

using namespace std;

const Node * GeometryNode::_intersect(
                                          const Ray &r,
                                          glm::dvec4 &p,
                                          glm::dvec4 &normal
                                          ) const {
  float t;
  bool res = prim->intersect(r, t, normal);
  if (res) {
    p = Ray::pointAt(r, t - constants::EPSILON);
    //DLOG_F(INFO, "hit %s %p", name.c_str(), (void*)&material);
    return this;
  }
  return nullptr;
}
