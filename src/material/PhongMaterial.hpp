#pragma once

#include <glm/glm.hpp>
#include "material/Material.hpp"
#include "Helpers.hpp"

#include <iostream>

struct PhongMaterial : public Material {
  const glm::dvec3 kd;
  const glm::dvec3 ks;
  const double shininess;

  PhongMaterial(
      const std::vector<double> &kd, 
      const std::vector<double> &ks,
      const double &shininess) : 
    kd(helpers::stdtoglm3(kd)),
    ks(helpers::stdtoglm3(ks)),
    shininess(shininess)
    {}

  virtual glm::dvec3 intersect(
    const Scene &scene,
    const Ray &rayFromEye,
    const int depth,
    const int curRefractionIndex,
    const glm::dvec4 &sceneHit,
    const glm::dvec4 &sceneHitNormal) const;
};
