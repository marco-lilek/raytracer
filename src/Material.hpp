#pragma once

#include "Scene.hpp"
#include "LightRay.hpp"
#include "Object.hpp"
#include "Color.hpp"

#include <glm/glm.hpp>

struct Material : public Object {

  virtual ~Material() {}

  virtual const char * type() const {
    return "Material";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
