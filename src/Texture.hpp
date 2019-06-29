#pragma once

#include "Object.hpp"
#include <glm/glm.hpp>
#include <vector>

struct Texture : public Object {
  std::vector<glm::dvec3> data;
  int width, height;
  
  Texture(int width, int height) : width(width), height(height) {
    data.resize(width * height);
  }

  glm::dvec3 getValue(double u, double v) const; 

  virtual const char * type() const {
    return "Texture";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
