#pragma once
#include "Intersection.hpp"
#include "Glm.hpp"

struct GeometryIntersection : public Intersection {
  // The point of intersection
  Glm::Vec4 p;

  // The normal at the point of intersection
  Glm::Vec4 n;

  GeometryIntersection(const ShooterPos sp,
      const Glm::Vec4 &p,
      const Glm::Vec4 &n) : 
    Intersection(sp), 
    p(p),
    n(n) {} 

  virtual const char * type() const {
    return "GeometryIntersection";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
    // TODO
  }
};
