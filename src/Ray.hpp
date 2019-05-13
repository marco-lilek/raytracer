#pragma once

#include "Point.hpp"
#include "Vector.hpp"

struct Ray {
  const Point from;
  const Vector v;

  Ray(const Point &from, const Vector &v)
      : from(from), v(v)
  {}
};
