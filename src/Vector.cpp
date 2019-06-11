#include "Vector.hpp"
#include "Constants.hpp"

Vector::Vector(double x, double y, double z) :
  glm::dvec4(x,y,z, 0)
{}

Vector::Vector(const glm::dvec4 &vv) :
  glm::dvec4(vv)
{}

Vector::Vector(const glm::dvec3 &vv) :
  glm::dvec4(vv, 0)
{}

Vector::Vector() :
  glm::dvec4(0)
{}

Vector Vector::cross(const Vector &o) const
{
  return glm::cross(glm::dvec3(*this), glm::dvec3(o));
}

Vector Vector::normalize() const
{
  return glm::normalize(glm::dvec3(*this));
}

double Vector::normalizeDot(const Vector &o) const {
  return glm::dot(
      glm::normalize(glm::dvec3(*this)), 
      glm::normalize(glm::dvec3(o)));
}

double Vector::dot(const Vector &o) const {
  return glm::dot(glm::dvec3(*this), glm::dvec3(o));
}

Vector Vector::halfwayVector(const Vector &o) const {
  const glm::dvec3 c = glm::dvec3(*this) + glm::dvec3(o);
  return c / (glm::length(c) + constants::EPSILON);
}

// n must be normalized
Vector Vector::reflectAcross(const Vector &n) const {
  const glm::dvec3 normalizedN(n);
  const glm::dvec3 d(*this);

  return d - 2 * glm::dot(d, normalizedN) * normalizedN;
}
