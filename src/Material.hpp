#pragma once

#include "Scene.hpp"
#include "LightRay.hpp"
#include "Object.hpp"
#include <glm/glm.hpp>

struct Material : public Object {
  virtual glm::dvec3 intersect(
    const Scene &scene,
    const LightRay &rayFromEye,
    const glm::dvec4 &sceneHit,
    const glm::dvec4 &sceneHitNormal) const = 0;
  virtual ~Material() {}

  virtual const char * type() const {
    return "Material";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
