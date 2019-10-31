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

// assumes n is normalized
glm::dvec3 maths::cosineDist(const glm::dvec3 &n) {
  // TODO explain why this works
  double sin_theta = glm::sqrt(maths::random0_1());
  double cos_theta = glm::sqrt(1 - sin_theta * sin_theta);

  double angleOnPlane = random0_1() * 2.0 * glm::pi<double>();

  double fNormLen = cos_theta;
  double fTangLen = glm::sin(angleOnPlane);
  double fBitgLen = glm::cos(angleOnPlane);

  // in this case since the random distribution is uniform we can pick
  // any arbitrary vector perp to n to define the plane
  // TODO probably a smarter way to do this
  glm::dvec3 arbit(n[0]+1.0, n[1], n[2]);
  glm::dvec3 tang = glm::normalize(glm::cross(n, arbit));
  glm::dvec3 bitg = glm::normalize(glm::cross(n, tang));

  glm::dvec3 final = fNormLen * n + fTangLen * tang + fBitgLen * bitg;
  return final;
}

double maths::random0_1() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<double> dis0_1(0.0, 1.0);
  return dis0_1(gen);
}

