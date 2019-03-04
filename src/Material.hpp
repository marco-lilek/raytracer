#pragma once

#include <glm/glm.hpp>
#include "Helpers.hpp"

#include <iostream>
struct Material {
  const glm::dvec3 kd;
  const glm::dvec3 ks;
  const double shininess;
  const double reflectiveness;

  Material(
      const std::vector<double> &kd, 
      const std::vector<double> &ks,
      const double &shininess,
      const double &reflectiveness) : 
    kd(helpers::stdtoglm3(kd)),
    ks(helpers::stdtoglm3(ks)),
    shininess(shininess),
    reflectiveness(reflectiveness) {}
};
