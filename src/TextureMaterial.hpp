#pragma once

#include "PhongMaterial.hpp"
#include "Texture.hpp"
#include "TextureLoader.hpp"
#include "Log.hpp"

#include <string>

struct TextureMaterial : public PhongMaterial {
  const Texture *texture;
  const Texture *bump;

  TextureMaterial(
      const char *textureName,
      const char *bumpName,
      const Glm::Vec3 &kd,
      const Glm::Vec3 &ks,
      const double shininess) : 
      PhongMaterial(kd, ks, shininess), 
      texture(!textureName ? NULL : TextureLoader::loadTexture(textureName)),
      bump(!bumpName ? NULL : TextureLoader::loadTexture(bumpName)) {
    const char *METHOD_NAME = "TextureMaterial::TextureMaterial";

    CHECK(METHOD_NAME, !textureName || texture != NULL);
    CHECK(METHOD_NAME, !bumpName || bump != NULL);
  }

  virtual ~TextureMaterial() {
    delete texture;
  }

  virtual const char * type() const {
    return "TextureMaterial";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Material::dump(o);
    if (texture) {
      o << "texture " << *texture;
    }

    if (bump) {
      o << "bump " << *bump;
    }
    return o;
  }
};
