#pragma once

#include <glm/glm.hpp>

namespace constants {
  extern const glm::vec4 POINT;
  extern const float EPSILON;
};

namespace helpers {
  float normalizedDot(const glm::vec4 &a, const glm::vec4 &b);
  glm::vec4 halfwayVector(const glm::vec4 &a, const glm::vec4 &b);
}