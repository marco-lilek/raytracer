#pragma once

#include "PhongMaterial.hpp"
#include "Texture.hpp"
#include "TextureLoader.hpp"
#include "Log.hpp"

#include <string>

struct TextureMaterial : public PhongMaterial {
  const Texture *texture;

  TextureMaterial(const std::string &name) : 
    PhongMaterial(Glm::Vec4(1), Glm::Vec4(1), 1), 
    texture(TextureLoader::loadTexture(name)) {

    CHECK("TextureMaterial::TextureMaterial", texture != NULL);
  }

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
