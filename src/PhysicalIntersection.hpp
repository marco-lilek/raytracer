#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "GeometryIntersection.hpp"
#include <memory>
#include "Log.hpp"

class PhysicalNode;

struct PhysicalIntersection : public Object {

  PhysicalIntersection(
      const PhysicalNode *hitNode, 
      GeometryIntersection *geometry) : 
    hitNode(hitNode),
    geometry(geometry) {
    const char *TRACE_HEADER = "PhysicalIntersection";
    Log::check(
        TRACE_HEADER, 
        hitNode != NULL && geometry != NULL, 
        "PhysicalIntersection malformed");
  }

  PhysicalIntersection() : 
    hitNode(NULL), 
    geometry(NULL) {
  }

  PhysicalIntersection(const PhysicalIntersection &o) : 
    hitNode(o.hitNode),
    geometry(o.geometry)
    {}

  ~PhysicalIntersection() {
  }

    
  // The node that we hit
  const PhysicalNode *hitNode;

  // How we intersected that node
  std::shared_ptr<GeometryIntersection> geometry;

  bool isHit() const {
    return geometry != NULL;
  }

  virtual const char * type() const {
    return "PhysicalIntersection";
  }

  virtual std::ostream& dump(std::ostream& o) const;
};
