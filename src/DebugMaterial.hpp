#pragma once

#include "Material.hpp"
#include "Object.hpp"
#include "GeometryIntersection.hpp"
#include "Glm.hpp"

#include <iostream>

struct DebugMaterial : public Material {

  DebugMaterial() : Material() {}

  Glm::Vec3 getColor(const GeometryIntersection::ShooterPos &shooterPos) const;

  virtual const char * type() const {
    return "DebugMaterial";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Material::dump(o);
    return o;
  }
};
