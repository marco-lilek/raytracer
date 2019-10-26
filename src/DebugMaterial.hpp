//
// Created by mllilek on 10/20/19.
//

#pragma once

#include "Material.hpp"

struct DebugMaterial : public Material {
  glm::dvec3 color;
  DebugMaterial(const glm::dvec3 &color) : color(color) {}
};

