#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Object.hpp"
#include "Point.hpp"

class Vector : public glm::dvec4, public Object {
public:
  Vector(double x, double y, double z);
  Vector(const Point &p) : glm::dvec4(p.x, p.y, p.z, 0) {}
  Vector(const glm::dvec3 &v);
  Vector(const glm::dvec4 &v);
  Vector();

  Vector normalize() const;
  Vector cross(const Vector &o) const;
  double dot(const Vector &o) const;
  double normalizeDot(const Vector &o) const;

  Vector halfwayVector(const Vector &o) const;
  // normalized!
  Vector reflectAcross(const Vector &normal) const;

  virtual const char * type() const {
    return "Vector";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << glm::to_string(static_cast<glm::dvec4>(*this));
  }
};
