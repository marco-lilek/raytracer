#pragma once

#include <glm/glm.hpp>

namespace constants {
  extern const glm::dvec4 ORIGIN;
  extern const float EPSILON;
};

namespace helpers {
  float normalizedDot(const glm::dvec4 &a, const glm::dvec4 &b);
  glm::dvec4 halfwayVector(const glm::dvec4 &a, const glm::dvec4 &b);
}
