#include <algorithm>
#include "Helpers.hpp"

const glm::dvec4 constants::ORIGIN(0,0,0,1);
const float constants::EPSILON = 0.0001;

float helpers::normalizedDot(const glm::dvec4 &a, const glm::dvec4 &b) {
  const glm::dvec4 normA = glm::normalize(a);
  const glm::dvec4 normB = glm::normalize(b);
  return std::max(0.0, glm::dot(normA, normB));
}

glm::dvec4 helpers::halfwayVector(const glm::dvec4 &a, const glm::dvec4 &b) {
  const glm::dvec4 c = a+b;
  return c / (glm::length(c) + constants::EPSILON);
}

glm::dvec3 helpers::stdtoglm3(const std::vector<double> &v) {
  return glm::dvec3(v[0], v[1], v[2]);
}

glm::dvec4 helpers::stdtoglm4(const std::vector<double> &v) {
  return glm::dvec4(v[0], v[1], v[2], v[3]);
}
