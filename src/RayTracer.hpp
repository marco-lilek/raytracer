#pragma once

#include "node/Node.hpp"

struct RayTracer {
  bool renderReflection;
  glm::dvec3 ambientLight;

  RayTracer() : 
    renderReflection(true),
    ambientLight(0.5) {}
  void render(const Node *rootNode);
};
