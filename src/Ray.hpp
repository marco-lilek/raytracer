#pragma once

#include "Glm.hpp"
#include "Object.hpp"

class Ray : public Object {
public:
  const Glm::Vec4 from;
  const Glm::Vec4 v;

  Glm::Vec4 pointAt(double t) const {
    return from + t * v;
  }

  Ray(const Glm::Vec4 &from, const Glm::Vec4 &v)
      : from(from), v(v)
  {}

  virtual const char * type() const {
    return "Ray";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << "from: " << from << " v: " << v;
  }
};
