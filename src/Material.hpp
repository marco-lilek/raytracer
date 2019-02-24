#pragma once

#include <glm/glm.hpp>

struct Material {
  const glm::vec3 kd;
  const glm::vec3 ks;
  const float shininess;

  Material(const glm::vec3 &kd, const glm::vec3 &ks, const float &shininess) : 
    kd(kd), ks(ks), shininess(shininess) {}
};