#pragma once

#include "node/Node.hpp"

struct RayTracer {
  bool renderReflection;

  RayTracer() : 
    renderReflection(true) {}

  void render(
    const Node *rootNode,
    const std::vector<const Light *> &lights,
    const std::string &fname,
    const int width,
    const int height,
    //const glm::dvec3 &eye, // TODO
    //const glm::dvec3 &view,
    //double fovy,
    const glm::dvec3 &ambient
              );

};
