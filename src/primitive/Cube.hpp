#pragma once

#include "primitive/Primitive.hpp"

class Cube : public Primitive {
public:
  virtual ~Cube() {}
  virtual bool intersect(const Ray &r, float &t, glm::dvec4 &normal) const;
};
