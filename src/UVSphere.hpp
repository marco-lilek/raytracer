#pragma once

#include "Sphere.hpp"

class UVSphere : public Sphere {
public:
  virtual ~UVSphere() {}
  virtual Intersection *intersect(const Ray &incomingRay) const;

  virtual const char * type() const {
    return "UVSphere";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Geometry::dump(o);
    return o;
  }
};
