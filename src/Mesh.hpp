#pragma once

#include "Primitive.hpp"
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class Mesh : public Primitive {
protected:
  std::vector<glm::dvec3> positions;

public:
  Mesh(
    const std::string &name);
  virtual ~Mesh() {};
  virtual bool intersect(
    const Ray &r, float &t, glm::dvec4 &normal) const;

  bool _intersect(
    const Ray &r, float &t, int &hitFace, double &beta, double &gamma) const;

  virtual void importElements(
    Assimp::Importer &importer,
    const aiScene *scene);

  bool verifyScene(
    const aiScene *scene);

};
