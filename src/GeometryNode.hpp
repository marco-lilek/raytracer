#pragma once

#include "Material.hpp"
#include "Node.hpp"
#include "Geometry.hpp"
#include "PhysicalNode.hpp"

class GeometryNode : public PhysicalNode {
  const Geometry *const geometry;

public:
  GeometryNode(
    const std::string &name,
    const Geometry *const p,
    const Material *m)
      : PhysicalNode(name, m), geometry(p)
  {}

  virtual const PhysicalIntersection intersectImpl(const Ray &r) const;

  virtual const char * type() const {
    return "GeometryNode";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Node::dump(o);
    return o << " geometry " << *geometry;
  }
};
