//
// Created by mllilek on 10/27/19.
//

#pragma once

#include "Medium.hpp"

struct RefractiveMaterial : public Material {
  std::unique_ptr<Medium> medium;
  RefractiveMaterial(Medium *m) : medium(m) {}
  ~RefractiveMaterial() {}
};

