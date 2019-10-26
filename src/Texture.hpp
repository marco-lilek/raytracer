//
// Created by mllilek on 10/22/19.
//

#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Texture {
  std::vector<glm::dvec3> data;
  int width, height;

  Texture(const std::string &name, const std::string &texture);

  glm::dvec3 getValue(double u, double v) const;
};

