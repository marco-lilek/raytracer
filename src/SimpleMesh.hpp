#pragma once

#include "Mesh.hpp"

class SimpleMesh : public Mesh {
public:

  SimpleMesh(const std::string &name);
  virtual ~SimpleMesh() {};

  virtual const char * type() const {
    return "SimpleMesh";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o;
  }

private:
  virtual Intersection *constructIntersection(
      int hitFace, Glm::Vec4 poi, double beta, double gamma) const;
};
