#pragma once

#include "Material.hpp"
#include <glm/glm.hpp>

#include <iostream>

struct PhongMaterial : public Material {
  const Color kd;
  const Color ks;

  const double shininess;

  PhongMaterial(
    const Color &kd,
    const Color &ks,
    const double &shininess) : 
    kd(kd), 
    ks(ks),
    shininess(shininess)
  {
  }

  virtual const char * type() const {
    return "PhongMaterial";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Material::dump(o);
    o << "kd " << kd << " ks " << ks << " shininess " << shininess;
    return o;
  }
};
