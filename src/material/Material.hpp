#pragma once

#include <glm/glm.hpp>
#include "Helpers.hpp"
#include "Ray.hpp"
#include "Scene.hpp"

struct Material {
  virtual glm::dvec3 intersect(
    const Scene &scene,
    const Ray &rayFromEye,
    const int depth,
    const int curRefractionIndex,
    const glm::dvec4 &sceneHit,
    const glm::dvec4 &sceneHitNormal) const 
  {
    return glm::dvec3(1);
  };
  virtual ~Material() {}
};
