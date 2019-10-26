#pragma once

#include "Ray.hpp"
#include "Intersection.hpp"

struct Geometry {
  virtual Intersection intersect(const Ray &incomingRay) const = 0;
  virtual bool isUV() const {
    return false;
  }
};