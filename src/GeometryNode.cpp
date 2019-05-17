#include "GeometryNode.hpp"
#include "Constants.hpp"
#include "Debug.hpp"
#include <iostream>

using namespace std;

const PhysicalIntersection GeometryNode::intersectImpl(const Ray &r) const {
  return PhysicalIntersection();
}
