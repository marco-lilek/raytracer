#pragma once

#include "node/Node.hpp"
#include "Primitive.hpp"
#include "Material.hpp"

class GeometryNode : public Node {
  const Primitive* const prim; // TODO put on the stack
  const Material material;

public:
  GeometryNode(const std::string &name, 
    const Primitive * const p, const Material &m) : 
    Node(name), prim(p), material(m) {}

  virtual const Material *intersectImpl(const Ray &r, glm::vec4 &p, glm::vec4 &normal) const;
};