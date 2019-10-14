#pragma once

#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <fmt/format.h>

namespace Glm {

  typedef glm::dvec4 Vec4;
  typedef glm::dvec3 Vec3;
  typedef glm::dvec2 Vec2;

  typedef glm::dmat4 Mat4;
  typedef glm::dmat3 Mat3;

  Vec4 cross(const Vec4 &a, const Vec4 &b);

  Vec4 normalize(const Vec4 &v);

  double normalizeDot(const Glm::Vec4 &a, const Glm::Vec4 &b);

  double dot(const Vec4 &a, const Vec4 &b);

  double distanceTo(const Glm::Vec4 &a, const Glm::Vec4 &b);

  Glm::Vec4 halfwayVector(const Glm::Vec4 &a, const Glm::Vec4 &b);
  Glm::Vec4 reflectAcross(const Glm::Vec4 &a, const Glm::Vec4 &n);
  Glm::Vec3 clamp(const Glm::Vec3 &v);

  // double cos(const Vec4&a, const vec4&b);
};

bool operator>=(const Glm::Vec3 &a, int v);

std::ostream& operator<<(std::ostream& out, const Glm::Vec4& g);
std::ostream& operator<<(std::ostream& out, const Glm::Vec3& g);

std::ostream& operator<<(std::ostream& out, const Glm::Mat4& g);
std::ostream& operator<<(std::ostream& out, const Glm::Mat3& g);
