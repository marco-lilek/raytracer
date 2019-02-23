#pragma once

#include <glm/glm.hpp>

#include "Ray.hpp"

class Primitive {
public:
  virtual ~Primitive() {}
  virtual bool intersect(const Ray &r, float &t, glm::vec4 &normal) const = 0;
};

class Sphere : public Primitive {
  double radius;
public:
  Sphere(const double &radius) : radius(radius) {}
  virtual ~Sphere() {}
  virtual bool intersect(const Ray &r, float &t, glm::vec4 &normal) const;
};

