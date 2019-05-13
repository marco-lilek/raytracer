#pragma once

#include <glm/glm.hpp>

class Vector {
  const glm::dvec3 v;

public:
  Vector(double x, double y, double z);
  Vector(const glm::dvec3 &vv);

  Vector cross(const Vector &o) const;
  Vector normalize() const;

  Vector operator *(double factor) const;
  Vector operator +(const Vector &other) const;
};
