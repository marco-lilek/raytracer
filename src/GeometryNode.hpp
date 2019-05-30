#pragma once

#include "Material.hpp"
#include "Node.hpp"
#include "Primitive.hpp"
#include "PhysicalNode.hpp"

class GeometryNode : public PhysicalNode {
  const Primitive *const prim;

public:
  GeometryNode(
    const std::string &name,
    const Primitive *const p,
    const Material *m)
      : PhysicalNode(name, m), prim(p)
  {}

  virtual const PhysicalIntersection intersectImpl(const Ray &r) const;

  virtual const char * type() const {
    return "GeometryNode";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Node::dump(o);
    return o << " prim " << *prim;
  }
};
