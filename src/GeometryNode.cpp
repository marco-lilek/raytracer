#include "GeometryNode.hpp"
#include "Constants.hpp"
#include "Debug.hpp"
#include "GeometryIntersection.hpp"
#include <iostream>

using namespace std;

const 
PhysicalIntersection GeometryNode::intersectImpl(const Ray &incomingRay) const {
  const char *METHOD_NAME = "GeometryNode::intersectImpl";
  Log::trace(METHOD_NAME, "incomingRay {}", incomingRay);

  Intersection *intersection = prim->intersect(incomingRay);
  Log::check(METHOD_NAME, intersection != NULL, "intersection should not be null");
  Log::trace(METHOD_NAME, "intersection {}", *intersection);
  if (intersection->isHit()) {
    return PhysicalIntersection(this, static_cast<GeometryIntersection*>(intersection));
  } else {
    // Need to deallocate it, for now we just treat all types of misses the same
    delete intersection;
    return PhysicalIntersection();
  }
}
