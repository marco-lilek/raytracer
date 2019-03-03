#pragma once

#include "primitive/Primitive.hpp"

class Sphere : public Primitive {
  double radius;
public:
  Sphere(const double &radius) : radius(radius) {}
  virtual ~Sphere() {}
  virtual bool intersect(const Ray &r, float &t, glm::dvec4 &normal) const;
};

