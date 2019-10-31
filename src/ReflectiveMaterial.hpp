//
// Created by mllilek on 10/27/19.
//

#pragma once

#include "GlossyMaterial.hpp"

// Just reflects
struct ReflectiveMaterial : public GlossyMaterial {
  ReflectiveMaterial() : GlossyMaterial() {}
  virtual ~ReflectiveMaterial() {}
};

