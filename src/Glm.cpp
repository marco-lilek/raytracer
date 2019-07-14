#include "Glm.hpp"
#include "Constants.hpp"

Glm::Vec4 Glm::cross(const Glm::Vec4 &a, const Glm::Vec4 &b) 
{
  // TODO assert a[3] == b[3]
  return Glm::Vec4(glm::cross(Vec3(a), Vec3(b)), a[3]);
}

Glm::Vec4 Glm::normalize(const Glm::Vec4 &v) 
{
  return Glm::Vec4(glm::normalize(Vec3(v)), v[3]);
}

double Glm::normalizeDot(const Glm::Vec4 &a, const Glm::Vec4 &b) {
  return Glm::dot(Glm::normalize(a), Glm::normalize(b));
}

double Glm::dot(const Glm::Vec4 &a, const Glm::Vec4 &b) {
  return glm::dot(Vec3(a), Vec3(b));
}

double Glm::distanceTo(
    const Glm::Vec4 &a,
    const Glm::Vec4 &b) {
  return glm::distance(Vec3(a), Vec3(b));
}

Glm::Vec4 Glm::halfwayVector(const Glm::Vec4 &a, const Glm::Vec4 &b) {
  const glm::dvec3 c = Glm::Vec3(a) + Glm::Vec3(b);
  return Glm::Vec4(c / (glm::length(c) + constants::EPSILON), 0); // To avoid dividing by 0
}

// n must be normalized
Glm::Vec4 Glm::reflectAcross(
    const Glm::Vec4 &a,
    const Glm::Vec4 &n) {
  const glm::dvec3 normalizedN(n);
  const glm::dvec3 d(a);

  return Glm::Vec4(d - 2 * glm::dot(d, normalizedN) * normalizedN, 0);
}

Glm::Vec3 Glm::clamp(const Glm::Vec3 &v) {
  return glm::clamp(v, Glm::Vec3(0), Glm::Vec3(1));
}

bool operator>=(const Glm::Vec3 &a, int v) {
  return a.x >= v && a.y >= v && a.z >= v;
}

std::ostream& operator<<(std::ostream& out, const Glm::Vec4& g) {
    return out << glm::to_string(g);
}

std::ostream& operator<<(std::ostream& out, const Glm::Vec3& g) {
    return out << glm::to_string(g);
}

std::ostream& operator<<(std::ostream& out, const Glm::Mat4& g) {
    return out << glm::to_string(g);
}

std::ostream& operator<<(std::ostream& out, const Glm::Mat3& g) {
    return out << glm::to_string(g);
}
