#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "GeometryIntersection.hpp"

class PhysicalNode;

// Could avoid wasting stack space when we have 
// an intersection that didn't hit
// ...but for now this is good enough, better than using the heap
// (so we can keep things running fast)
struct PhysicalIntersection : public Object, public Intersection {

  PhysicalIntersection(const PhysicalNode *hitNode, 
      const GeometryIntersection &geometry) : 
    hitNode(hitNode),
    geometry(geometry) {}

  PhysicalIntersection() :
    hitNode(nullptr),
    geometry(GeometryIntersection::Miss) {}
    
  // The node that we hit
  const PhysicalNode *hitNode;

  GeometryIntersection geometry;

  virtual const char * type() const {
    return "PhysicalIntersection";
  }

  virtual std::ostream& dump(std::ostream& o) const;

  virtual bool isHit() const {
    return geometry.isHit();
  }
};
