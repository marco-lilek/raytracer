#pragma once

#include <glm/glm.hpp>
#include <ostream>
#include <glm/gtx/string_cast.hpp>

#include "Object.hpp"

class Point : public glm::dvec4, public Object {
public:
  Point(double x, double y, double z) : glm::dvec4(x,y,z,1) {}
  Point(const glm::dvec3 &in) : glm::dvec4(in, 1) {}

  virtual const char * type() const {
    return "Point";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << glm::to_string(static_cast<glm::dvec4>(*this));
  }
};

