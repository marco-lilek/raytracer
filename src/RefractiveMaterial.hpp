#pragma once

#include "Material.hpp"
#include <glm/glm.hpp>

struct RefractiveMaterial : public Material {

  const double indexOfRefraction;

  RefractiveMaterial(const double indexOfRefraction)
      : Material(), indexOfRefraction(indexOfRefraction)
  {}

  virtual ~RefractiveMaterial() {}

  virtual const char * type() const {
    return "RefractiveMaterial";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
