#pragma once

#include "Material.hpp"
#include "Node.hpp"
#include "Geometry.hpp"

struct Geometry;
struct Texture;

struct GeometryNode : public Node {
  Material *m;
  Texture *bump;

  const Geometry *g;

  GeometryNode(const std::string &name, const Geometry *g) :
    Node(name), m(nullptr), g(g), bump(nullptr) {}
  ~GeometryNode() override {};

  bool isUV() const {
    return g != nullptr && g->isUV();
  }

private:
  virtual Intersection intersectImpl(const Ray &incomingRay) const;
};

