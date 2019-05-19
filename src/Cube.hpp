#pragma once

#include "Primitive.hpp"

class Cube : public Primitive {
public:
  virtual ~Cube() {}
  virtual GeometryIntersection intersect(const Ray &incomingRay) const {
    // Stub
    return GeometryIntersection();
  }

  virtual const char * type() const {
    return "Cube";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Primitive::dump(o);
    return o;
  }
};
