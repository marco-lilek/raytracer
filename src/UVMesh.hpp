#pragma once

#include "Mesh.hpp"
#include <string>
#include <vector>

class UVMesh : public Mesh {
  std::vector<glm::dvec3> normals;
  std::vector<glm::dvec2> uvCoords;
  std::vector<glm::dvec3> tangents;

public:
  UVMesh(const std::string &name) : Mesh(name) {}

  virtual ~UVMesh() {};

  virtual void importElements(
    Assimp::Importer &importer,
    const aiScene *scene);

  virtual const char * type() const {
    return "UVMesh";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
