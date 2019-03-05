#pragma once

#include "Ray.hpp"
#include "Color.hpp"
#include "Light.hpp"
#include <vector>

class Node;

struct Scene {
  const Node * const root;
  const std::vector<const Light *> lights;
  const glm::dvec3 fireRay(
      const Ray &r,
      const int depth,
      const double curRefractionIndex
      ) const;

public:
  Scene(const Node * const root, const std::vector<const Light *> &lights);
  static const Ray constructRay(int x, int y, int width, int height);
  const Color getColor(const Ray &r) const;
};
