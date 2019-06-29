#pragma once

#include "GeometryIntersection.hpp"

struct UVIntersection : public GeometryIntersection {
  double u, v;

  UVIntersection(const ShooterPos sp,
      const Point &p,
      const Vector &n,
      const double u,
      const double v) : 
    GeometryIntersection(sp, p, n),
    u(u),
    v(v) {}

  virtual const char * type() const {
    return "UVIntersection";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
