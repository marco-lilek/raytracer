#pragma once

#include "Material.hpp"

#include <iostream>

struct PhongMaterial : public Material {
  const glm::dvec3 kd;
  const glm::dvec3 ks;

  const double shininess;

  PhongMaterial(
    const glm::dvec3 &kd,
    const glm::dvec3 &ks,
    const double &shininess) : 
    kd(kd), 
    ks(ks),
    shininess(shininess)
  { }
};
