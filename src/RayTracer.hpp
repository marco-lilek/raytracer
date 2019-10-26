#pragma once

#include <string>
#include <list>
#include <vector>

#include "Node.hpp"
#include "Light.hpp"
#include "Image.hpp"

struct RayTracer {
  bool renderReflection;

  RayTracer() : renderReflection(true) {}

  static void render(
          const Node *rootNode,
          Image &image,
          const glm::dvec3 &eye,
          const glm::dvec3 &view,
          const glm::dvec3 &up,
          const double &fov,
          const glm::dvec3 &ambient,
          std::vector<const Light *> lights);
};
