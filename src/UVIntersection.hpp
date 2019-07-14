#pragma once

#include "GeometryIntersection.hpp"

struct UVIntersection : public GeometryIntersection {
  double u, v;
  // tangent
  Glm::Vec4 t;

  UVIntersection(const ShooterPos sp,
      const Glm::Vec4 &p,
      const Glm::Vec4 &n,
      const Glm::Vec4 &t,
      const double u,
      const double v) : 
    GeometryIntersection(sp, p, n),
    t(t),
    u(u),
    v(v) {}

  virtual const char * type() const {
    return "UVIntersection";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
