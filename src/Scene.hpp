#pragma once

#include "Ray.hpp"
#include "node/Node.hpp"
#include "Color.hpp"
#include "Light.hpp"

class Scene {
  const Node * const root;
  const std::vector<const Light *> lights;
  const glm::dvec3 ambientLight;
  const glm::dvec3 fireRay(const Ray &r, const int depth) const;

public:
  Scene(const Node * const root, const std::vector<const Light *> &lights);
  static const Ray constructRay(int x, int y, int width, int height);
  const Color getColor(const Ray &r) const;
};