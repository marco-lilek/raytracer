#pragma once

#include "Material.hpp"

#include <iostream>

#include "Glm.hpp"

struct PhongMaterial : public Material {
  const Glm::Vec3 kd;
  const Glm::Vec3 ks;

  const double shininess;

  PhongMaterial(
    const Glm::Vec3 &kd,
    const Glm::Vec3 &ks,
    const double &shininess) : 
    kd(kd), 
    ks(ks),
    shininess(shininess)
  { }

  virtual const char * type() const {
    return "PhongMaterial";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Material::dump(o);
    o << "kd " << kd << " ks " << ks << " shininess " << shininess;
    return o;
  }
};
