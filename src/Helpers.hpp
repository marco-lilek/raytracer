#pragma once

#include <glm/glm.hpp>

namespace constants {
  extern const glm::vec4 POINT;
  extern const float EPSILON;
};

namespace helpers {
  float normDot(const glm::vec4 &a, const glm::vec4 &b);
}