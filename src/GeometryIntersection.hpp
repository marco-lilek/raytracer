#pragma once
#include "Intersection.hpp"
#include "Point.hpp"
#include "Vector.hpp"

struct GeometryIntersection : public Intersection {
  // The point of intersection
  Point p;

  // The normal at the point of intersection
  Vector n;

  GeometryIntersection(const ShooterPos sp,
      const Point &p,
      const Vector &n) : 
    Intersection(sp), 
    p(p),
    n(n) {} 

  virtual const char * type() const {
    return "GeometryIntersection";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
