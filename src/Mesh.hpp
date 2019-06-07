#pragma once

#include "Primitive.hpp"
#include <string>
#include <vector>
#include "MeshLoader.hpp"

class Mesh : public Primitive {
protected:
  std::vector<glm::dvec3> positions;

public:
  Mesh(const std::string &name);
  virtual ~Mesh() {};

  virtual GeometryIntersection intersect(const Ray &incomingRay) const;

  // The MeshLoader will load the Mesh on initialization
  friend class MeshLoader;

  virtual const char * type() const {
    return "Mesh";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }
};
