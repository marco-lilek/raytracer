#pragma once

#include "primitive/Primitive.hpp"
#include <string>
#include <vector>

class Mesh : public Primitive {
  std::vector<glm::vec3> positions;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvCoords;
  std::vector<glm::vec3> tangents;

public:
  Mesh(const std::string &name);
  virtual bool intersect(
    const Ray &r, float &t, glm::dvec4 &normal) const;
};
