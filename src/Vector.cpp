#include "Vector.hpp"

Vector::Vector(double x, double y, double z) :
  glm::dvec4(x,y,z, 0)
{}

Vector::Vector(const glm::dvec4 &vv) :
  glm::dvec4(vv)
{}

Vector::Vector(const glm::dvec3 &vv) :
  glm::dvec4(vv, 0)
{}

Vector Vector::cross(const Vector &o) const
{
  return Vector(glm::cross(glm::dvec3(*this), glm::dvec3(o)));
}

Vector Vector::normalize() const
{
  return Vector(glm::normalize(glm::dvec3(*this)));
}
