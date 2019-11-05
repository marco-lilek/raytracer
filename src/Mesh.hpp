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
  std::string fname;
  std::vector<glm::dvec3> positions;

  Mesh(const std::string &name, const std::string &fname);

  Intersection intersect(const Ray &incomingRay) const override;

  void load();

  virtual ~Mesh() {};
};
