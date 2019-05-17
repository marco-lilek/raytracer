#pragma once

#include <glm/glm.hpp>

#include "Ray.hpp"
#include "GeometryIntersection.hpp"

class Primitive : public Object {
public:
  virtual ~Primitive() {}

  virtual GeometryIntersection intersect(const Ray &incomingRay) {
    // Stub
    return GeometryIntersection();
  } 

  virtual const char * type() const {
    return "Primitive";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
