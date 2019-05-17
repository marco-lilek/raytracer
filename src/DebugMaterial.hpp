#pragma once

#include "Material.hpp"
#include "Object.hpp"
#include <glm/glm.hpp>

#include <iostream>

struct DebugMaterial : public Material {

  DebugMaterial() : Material() {}

  virtual glm::dvec3
  intersect(
    const Scene &scene,
    const LightRay &rayFromEye,
    const glm::dvec4 &sceneHit,
    const glm::dvec4 &sceneHitNormal) const {
    return glm::dvec3(1);
  }

  virtual const char * type() const {
    return "DebugMaterial";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Material::dump(o);
    return o;
  }
};
