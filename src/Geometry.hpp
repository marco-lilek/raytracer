#pragma once

#include <glm/glm.hpp>

#include "Ray.hpp"
#include "Intersection.hpp"

class Geometry : public Object {
public:
  virtual ~Geometry() {}

  // Allocates a new intserection on the heap
  // caller must deallocate
  virtual Intersection *intersect(const Ray &incomingRay) const {
    return new Intersection(Intersection::Miss);
  } 

  virtual const char * type() const {
    return "Geometry";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
