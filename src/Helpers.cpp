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
