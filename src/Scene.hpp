#pragma once

#include "Ray.hpp"
#include "node/Node.hpp"
#include "Color.hpp"
#include "Light.hpp"

class Scene {
  const Node * const root;
  const std::vector<const Light *> lights;
  const glm::vec3 ambientLight;

public:
  Scene(const Node * const root, const std::vector<const Light *> &lights);
  static Ray constructRay(int x, int y, int width, int height);
  Color fireRay(const Ray &r);
};