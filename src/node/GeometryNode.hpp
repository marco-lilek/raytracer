#pragma once

#include "node/Node.hpp"
#include "primitive/Primitive.hpp"
#include "Material.hpp"

class GeometryNode : public Node {
  const Primitive* const prim;
  const Material material;

public:
  GeometryNode(const std::string &name, 
    const Primitive * const p, const Material &m) : 
    Node(name), prim(p), material(m) {}

  virtual const Material *intersectImpl(const Ray &r, glm::dvec4 &p, glm::dvec4 &normal) const;
};
