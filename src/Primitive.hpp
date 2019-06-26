#pragma once

#include <glm/glm.hpp>

#include "Ray.hpp"
#include "Intersection.hpp"

class Primitive : public Object {
public:
  virtual ~Primitive() {}

  // Allocates a new intserection on the heap
  // caller must deallocate
  virtual Intersection *intersect(const Ray &incomingRay) const {
    return new Intersection(Intersection::Miss);
  } 

  virtual const char * type() const {
    return "Primitive";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
