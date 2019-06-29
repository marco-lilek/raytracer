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

  virtual const char * type() const {
    return "UVMesh";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
  friend class MeshLoader;

private:

  virtual Intersection *constructIntersection(
      int hitFace, Point poi, double beta, double gamma) const;
};
