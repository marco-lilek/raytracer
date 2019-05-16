#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Object.hpp"

class Vector : public glm::dvec4, public Object {
public:
  Vector(double x, double y, double z);
  Vector(const glm::dvec3 &v);
  Vector(const glm::dvec4 &v);

  Vector normalize() const;
  Vector cross(const Vector &o) const;

  virtual const char * type() const {
    return "Vector";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << glm::to_string(static_cast<glm::dvec4>(*this));
  }
};
