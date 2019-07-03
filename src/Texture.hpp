#pragma once

#include "Object.hpp"
#include "Glm.hpp"
#include <vector>

struct Texture : public Object {
  std::vector<Glm::Vec3> data;
  int width, height;
  
  Texture(int width, int height) : 
    width(width),
    height(height) {
    data.resize(width * height);
  }

  Glm::Vec3 getValue(double u, double v) const; 

  virtual const char * type() const {
    return "Texture";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
