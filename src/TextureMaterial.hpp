#pragma once

#include "PhongMaterial.hpp"
#include "Texture.hpp"
#include "TextureLoader.hpp"

#include <glm/glm.hpp>

#include <string>

struct TextureMaterial : public PhongMaterial {
  const Texture *texture;

  TextureMaterial(const std::string &name) : 
    PhongMaterial(Color(0), Color(0), 0), 
    texture(TextureLoader::loadTexture(name)) {}

  virtual ~TextureMaterial() {
    delete texture;
  }

  virtual const char * type() const {
    return "TextureMaterial";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Material::dump(o);
    o << "texture " << *texture;
    return o;
  }
};
