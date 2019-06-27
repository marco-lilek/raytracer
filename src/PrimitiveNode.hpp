#pragma once

#include "Material.hpp"
#include "Node.hpp"
#include "GeometryNode.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"

class PrimitiveNode : public GeometryNode {
  static Cube cube;
  static Sphere sphere;

  Geometry *getGeometryFromType(const std::string &type) const;

public:
  PrimitiveNode(
    const std::string &name,
    const std::string &type,
    const Material *m)
      : GeometryNode(name, getGeometryFromType(type), m)
  {}

  virtual const char * type() const {
    return "PrimitiveNode";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    GeometryNode::dump(o);
    return o;
  }
}; 
