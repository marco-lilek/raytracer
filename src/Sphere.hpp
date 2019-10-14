#pragma once

#include "Geometry.hpp"
#include "GeometryIntersection.hpp"

class Sphere : public Geometry {
public:
  virtual ~Sphere() {}
  virtual GeometryIntersection *intersect(const Ray &incomingRay) const;

  virtual const char * type() const {
    return "Sphere";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Geometry::dump(o);
    return o;
  }
};
