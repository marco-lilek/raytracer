#include "Math.hpp"
#include "Constants.hpp"
#include <algorithm>

double math::normalizedDot(const glm::dvec4 &a, const glm::dvec4 &b) {
  const glm::dvec4 normA = glm::normalize(a);
  const glm::dvec4 normB = glm::normalize(b);
  return std::max(0.0, glm::dot(normA, normB));
}

glm::dvec4 math::halfwayVector(const glm::dvec4 &a, const glm::dvec4 &b) {
  const glm::dvec4 c = a+b;
  return c / (glm::length(c) + constants::EPSILON);
}
