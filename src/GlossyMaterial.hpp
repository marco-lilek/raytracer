//
// Created by mllilek on 10/30/19.
//

#include "Material.hpp"

struct GlossyMaterial : public Material {
  double glossiness;
  GlossyMaterial() : glossiness(0.0) {}
  virtual ~GlossyMaterial() {}
};

