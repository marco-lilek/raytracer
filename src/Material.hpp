#pragma once

#include <glm/glm.hpp>

struct Material {
  const glm::dvec3 kd;
  const glm::dvec3 ks;
  const float shininess;

  Material(const glm::dvec3 &kd, const glm::dvec3 &ks, const float &shininess) : 
    kd(kd), ks(ks), shininess(shininess) {}
};