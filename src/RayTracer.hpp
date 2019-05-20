#pragma once

#include <string>
#include <vector>

#include "Node.hpp"
#include "Light.hpp"
#include "Camera.hpp"

struct RayTracer {
  bool renderReflection;

  RayTracer() : renderReflection(true) {}

  void render(
    const Node *rootNode,
    const Camera &c,
    const std::vector<const Light *> &lights,
    const std::string &fname,
    const int width,
    const int height);
};
