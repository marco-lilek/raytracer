#pragma once

#include "Material.hpp"
#include "Node.hpp"
#include "Primitive.hpp"

class GeometryNode : public Node {
const Primitive *const prim;
  const Material *material;

public:
  GeometryNode(
    const std::string &name,
    const Primitive *const p,
    const Material *m)
      : Node(name), prim(p), material(m)
  {
  }

  virtual const Node *_intersect(
    const Ray &r, glm::dvec4 &p, glm::dvec4 &normal) const;

  virtual glm::dvec3
  getColor(
    const Scene &scene,
    const LightRay &incomingRay,
    const glm::dvec4 &sceneHit,
    const glm::dvec4 &sceneHitNormal) const
  {
    return material->intersect(
      scene, incomingRay, sceneHit, sceneHitNormal);
  }
};