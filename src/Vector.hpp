#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Object.hpp"

class Vector : public Object {
  const glm::dvec3 v;

public:
  Vector(double x, double y, double z);
  Vector(const glm::dvec3 &vv);

  Vector cross(const Vector &o) const;
  Vector normalize() const;

  Vector operator *(double factor) const;
  Vector operator +(const Vector &other) const;

  virtual const char * type() const {
    return "Vector";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << glm::to_string(v);
  }
};
