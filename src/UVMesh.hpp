#pragma once

#include "Mesh.hpp"
#include <string>
#include <vector>

class UVMesh : public Mesh {
  std::vector<Glm::Vec3> normals;
  std::vector<Glm::Vec2> uvCoords;
  std::vector<Glm::Vec3> tangents;

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
      int hitFace, Glm::Vec4 poi, double beta, double gamma) const;
};
