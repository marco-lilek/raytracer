#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "Object.hpp"

class Ray : public Object {
public:
  const Point from;
  const Vector v;

  Ray(const Point &from, const Vector &v)
      : from(from), v(v)
  {}

  virtual const char * type() const {
    return "Ray";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << "from: " << from << " v: " << v;
  }
};
