#pragma once

#include "Geometry.hpp"

class Cube : public Geometry {
public:
  virtual ~Cube() {}
  virtual Intersection *intersect(const Ray &incomingRay) const;

  virtual const char * type() const {
    return "Cube";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Geometry::dump(o);
    return o;
  }
};
