#pragma once

#include <glm/glm.hpp>

struct Ray {
  const glm::vec4 from;
  const glm::vec4 v;

  Ray(const glm::vec4 &from, const glm::vec4 &v) : 
    from(from), v(v) {}

  glm::vec4 pointAt(const float &t) const {
    return from + v * t;
  }
};