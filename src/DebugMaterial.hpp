#pragma once

#include "Material.hpp"
#include "Object.hpp"
#include "GeometryIntersection.hpp"
#include <glm/glm.hpp>

#include <iostream>

struct DebugMaterial : public Material {

  DebugMaterial() : Material() {}

  Color getColor(const GeometryIntersection::ShooterPos &shooterPos) const;

  virtual const char * type() const {
    return "DebugMaterial";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Material::dump(o);
    return o;
  }
};
