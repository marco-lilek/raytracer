#pragma once

#include "Material.hpp"
#include "Texture.hpp"

#include <string>

struct TextureLoader {
  static const Texture *loadTexture(const std::string &name);
};
