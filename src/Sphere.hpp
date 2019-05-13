#pragma once

#include "Primitive.hpp"

class Sphere : public Primitive {
public:
  virtual ~Sphere() {}
  virtual bool intersect(
    const Ray &r, float &t, glm::dvec4 &normal) const;
};
