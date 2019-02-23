#pragma once

#include "node/Node.hpp"
#include "Primitive.hpp"

class GeometryNode : public Node {
  const Primitive* const prim;

public:
  GeometryNode(const std::string &name, const Primitive * const p) : 
    Node(name), prim(p) {}

  virtual bool intersectImpl(const Ray &r, glm::vec4 &p, glm::vec4 &normal) const;
};