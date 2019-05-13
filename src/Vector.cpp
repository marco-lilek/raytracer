#include "Vector.hpp"

Vector::Vector(double x, double y, double z) :
  v(x,y,z)
{}

Vector::Vector(const glm::dvec3 &vv) :
  v(vv)
{}

Vector Vector::cross(const Vector &o) const
{
  return Vector(glm::cross(this->v, o.v));
}

Vector Vector::normalize() const
{
  return Vector(glm::normalize(v));
}

Vector Vector::operator *(double factor) const
{
  return Vector(v * factor);
}

Vector Vector::operator +(const Vector &o) const
{
  return Vector(v + o.v);
}

