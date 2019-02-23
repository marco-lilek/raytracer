#pragma once

#include "Ray.hpp"
#include "node/Node.hpp"
#include "Color.hpp"

class Scene {
  const Node * const root;
public:
  Scene(const Node * const root);
  static Ray constructRay(int x, int y, int width, int height);
  Color fireRay(const Ray &r);
};