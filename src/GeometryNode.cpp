//
// Created by mllilek on 10/19/19.
//

#include "Geometry.hpp"
#include "GeometryNode.hpp"

Intersection GeometryNode::intersectImpl(const Ray &incomingRay) const {
  Intersection intersection = g->intersect(incomingRay);
  intersection.node = this;
  return intersection;
}
