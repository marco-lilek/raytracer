#pragma once

#include <glm/glm.hpp>

struct Ray {
  const glm::vec4 from;
  const glm::vec4 to;

  Ray(const glm::vec4 &from, const glm::vec4 &to) : 
    from(from), to(to) {}

  glm::vec4 pointAt(const float &t) const {
    glm::vec4 d = to - from;
    return from + d * t;
  }
};