#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "GeometryIntersection.hpp"

// Forward declare because of circular dependency
class PhysicalNode;

// TODO Could avoid wasting stack space when we have 
// an intersection that didn't hit
// ...but for now this is good enough, better than using the heap
// (so we can keep things running fast)
struct PhysicalIntersection : public GeometryIntersection {

  PhysicalIntersection(const PhysicalNode *hitNode,
      const Point &p,
      const Vector &n) : 
    GeometryIntersection(p, n),
    hitNode(hitNode) {}

  PhysicalIntersection() : GeometryIntersection(), hitNode(nullptr) {}

  // The node that we hit
  const PhysicalNode *hitNode;
};
