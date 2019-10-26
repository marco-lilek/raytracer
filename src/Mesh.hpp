#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include "Geometry.hpp"

struct Mesh : public Geometry {
  std::string name;
  std::vector<glm::dvec3> positions;

  Mesh(const std::string &name);

  Intersection intersect(const Ray &incomingRay) const override;

  virtual ~Mesh() {};
};
