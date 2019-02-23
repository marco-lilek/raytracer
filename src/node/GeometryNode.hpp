#pragma once

#include "node/Node.hpp"
#include "Primitive.hpp"

class GeometryNode : public Node {
  const Primitive* const p;

public:
  GeometryNode(const std::string &name, const Primitive * const p) : 
    Node(name), p(p) {}

  virtual bool intersect(const Ray &r, float &t, glm::vec4 &normal) const;
};