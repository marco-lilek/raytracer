#include "GeometryNode.hpp"
#include "Constants.hpp"
#include "Debug.hpp"
#include <iostream>

using namespace std;

const 
PhysicalIntersection GeometryNode::intersectImpl(const Ray &incomingRay) const {
  const char *METHOD_NAME = "GeometryNode::intersectImpl";
  Log::trace(METHOD_NAME, "incomingRay {}", incomingRay);

  GeometryIntersection geometryIntersection = prim->intersect(incomingRay);
  Log::trace(METHOD_NAME, "geometryIntersection {}", geometryIntersection);
  if (geometryIntersection.hit) {
    return PhysicalIntersection(this, geometryIntersection);
  } else {
    return PhysicalIntersection();
  }
}
