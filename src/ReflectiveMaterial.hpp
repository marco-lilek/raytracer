#pragma once

#include "Material.hpp"
#include <glm/glm.hpp>

// Reflective material--no refraction
struct ReflectiveMaterial : public Material {

  ReflectiveMaterial()
      : Material()
  {}

  virtual ~ReflectiveMaterial() {}

  virtual const char * type() const {
    return "ReflectiveMaterial";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
