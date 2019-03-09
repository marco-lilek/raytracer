#pragma once

#include <glm/glm.hpp>
#include "ray/LightRay.hpp"
#include "Scene.hpp"

struct Material {
  virtual glm::dvec3 intersect(
    const Scene &scene,
    const LightRay &rayFromEye,
    const glm::dvec4 &sceneHit,
    const glm::dvec4 &sceneHitNormal
                               ) const =0;
  virtual ~Material() {}
};
