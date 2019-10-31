//
// Created by mllilek on 10/27/19.
//

#pragma once

#include "Medium.hpp"

struct RefractiveMaterial : public GlossyMaterial {
  std::unique_ptr<Medium> medium;
  RefractiveMaterial(Medium *m) : GlossyMaterial(), medium(m) {}
  virtual ~RefractiveMaterial() {}
};

