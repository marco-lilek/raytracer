#pragma once

#include <glm/glm.hpp>

#include "ray/Ray.hpp"

class Primitive {
public:
  virtual ~Primitive() {}
  virtual bool intersect(const Ray &r, float &t, glm::dvec4 &normal) const = 0;
};

