#pragma once

#include "Primitive.hpp"

class Sphere : public Primitive {
public:
  virtual ~Sphere() {}
  virtual GeometryIntersection intersect(const Ray &incomingRay) const;

  virtual const char * type() const {
    return "Sphere";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Primitive::dump(o);
    return o;
  }
};
