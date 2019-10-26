#pragma once

#include <vector>

#include <glm/glm.hpp>

struct Light {
  glm::dvec3 colour;
  glm::dvec3 position;
  glm::dvec3 falloff;

  Light() {

  }
};

