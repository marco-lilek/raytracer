#pragma once

#include <glm/glm.hpp>

struct Light {
  const glm::dvec3 color;
  const glm::dvec4 pos;
  Light(const glm::dvec3 &color, glm::dvec4 pos) : 
    color(color), pos(pos) {}
};