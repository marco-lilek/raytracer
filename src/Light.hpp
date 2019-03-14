#pragma once

#include <vector>

#include <glm/glm.hpp>

struct Light {
  const glm::dvec3 color;
  const glm::dvec4 pos;
  Light(const glm::dvec3 &color, glm::dvec3 pos)
      : color(color), pos(glm::dvec4(pos, 1))
  {
  }
};
