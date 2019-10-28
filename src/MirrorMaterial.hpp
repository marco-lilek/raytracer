//
// Created by mllilek on 10/27/19.
//

#pragma once

#include "ReflectiveMaterial.hpp"

// Just reflects
struct MirrorMaterial : public ReflectiveMaterial {
  MirrorMaterial() {}
  ~MirrorMaterial() {}
};

