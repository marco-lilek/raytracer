#pragma once

#include <glm/glm.hpp>
#include <ostream>
#include <glm/gtx/string_cast.hpp>

#include "Object.hpp"

class Point : public Object {
const glm::dvec3 p;

public:
  Point(double x, double y, double z) : p(x,y,z) {}
  Point(const glm::dvec3 &in) : p(in) {}

  double operator[](int i) const {
    return p[i];
  }

  virtual const char * type() const {
    return "Point";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << glm::to_string(p);
  }
};

