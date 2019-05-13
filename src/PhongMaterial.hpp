#pragma once

#include "Material.hpp"
#include <glm/glm.hpp>

#include <iostream>

struct PhongMaterial : public Material {
  const glm::dvec3 kd;
  const glm::dvec3 ks;
  const double shininess;

  PhongMaterial(
    const glm::dvec3 &kd,
    const glm::dvec3 &ks,
    const double &shininess)
      : kd(kd), ks(ks), shininess(shininess)
  {
  }

  virtual glm::dvec3 intersect(
    const Scene &scene,
    const LightRay &rayFromEye,
    const glm::dvec4 &sceneHit,
    const glm::dvec4 &sceneHitNormal) const;
};