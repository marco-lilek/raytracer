#pragma once

#include <glm/glm.hpp>

struct Light {
  const glm::vec3 color;
  const glm::vec4 pos;
  Light(const glm::vec3 &color, glm::vec4 pos) : 
    color(color), pos(pos) {}
};