#pragma once

#include "Color.hpp"
#include "Light.hpp"
#include "ray/LightRay.hpp"
#include <vector>

class Node;

struct Scene {
  const Node *const root;
  const std::vector<const Light *> lights;
  const glm::dvec3 ambientLight;

  const glm::dvec3 fireRay(const LightRay &r) const;

public:
  Scene(
    const Node *const root,
    const std::vector<const Light *> &lights,
    const glm::dvec3 &ambient);
  static const LightRay
  constructRay(int x, int y, int width, int height);
  const Color getColor(const LightRay &r) const;
};
