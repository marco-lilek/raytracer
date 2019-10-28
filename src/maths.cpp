//
// Created by mllilek on 10/19/19.
//

#include <glm/detail/type_vec.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "maths.hpp"
#include "constants.hpp"

double maths::distance3d(const glm::dvec3 &a, const glm::dvec3 &b) {
  return glm::distance(a, b);
}

glm::vec3 maths::traceRay(const glm::dvec3 &p, const glm::dvec3 &v, double t) {
  return p + v * t;
}

bool maths::allGt(const glm::dvec3 &v, double c) {
  return v.x >= c && v.y >= c && v.z >= c;
}

double maths::normalizeDot3d(const glm::dvec3 &a, const glm::dvec3 &b) {
  return glm::dot(glm::normalize(a), glm::normalize(b));
}

glm::vec3 maths::halfwayVector3d(const glm::dvec3 &a, const glm::dvec3 &b) {
  const glm::dvec3 c = a + b;
  return c / (glm::length(c) + constants::EPSILON); // To avoid dividing by 0
}

glm::dvec3 maths::cross3d(const glm::dvec3 &a, const glm::dvec3 &b) {
  return glm::cross(a, b);
}

glm::dvec3 maths::normalize3d(const glm::dvec3 &a) {
  return glm::normalize(a);
}

glm::dvec3 maths::reflect3d(const glm::dvec3 &a, const glm::dvec3 &n) {
  const glm::dvec3 normalizedN(glm::normalize(n));
  return a - 2 * glm::dot(a, normalizedN) * normalizedN;
}

double maths::angle3d(const glm::dvec3 &a, const glm::dvec3 &b) {
  return glm::angle(glm::normalize(a), glm::normalize(b));
}
