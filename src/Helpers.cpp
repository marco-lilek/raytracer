#include <algorithm>
#include "Helpers.hpp"

const glm::vec4 constants::POINT(0,0,0,1);
const float constants::EPSILON = 0.0001;

float helpers::normalizedDot(const glm::vec4 &a, const glm::vec4 &b) {
  const glm::vec4 normA = glm::normalize(a);
  const glm::vec4 normB = glm::normalize(b);
  return std::max(0.0f, glm::dot(normA, normB));
}

glm::vec4 helpers::halfwayVector(const glm::vec4 &a, const glm::vec4 &b) {
  const glm::vec4 c = a+b;
  return c / glm::length(c);
}