#pragma once

#include <string>
#include <vector>
#include "Geometry.hpp"
#include "Glm.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class Mesh : public Geometry {

  std::string name;

protected:
  std::vector<Glm::Vec3> positions;

  const int loadPositions(
      const aiMesh* aiMesh);

  const aiScene *loadScene(
      Assimp::Importer &importer) const;

  bool verifyScene(const aiScene *scene) const;

public:
  Mesh(const std::string &name);
  virtual ~Mesh() {};

  virtual Intersection *intersect(const Ray &incomingRay) const;

  virtual const char * type() const {
    return "Mesh";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }

private:
  virtual Intersection *constructIntersection(
      int hitFace, Glm::Vec4 poi, double beta, double gamma) const = 0;

};
