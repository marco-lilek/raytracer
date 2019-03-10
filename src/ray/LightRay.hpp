#pragma once

#include "ray/Ray.hpp"

struct LightRay : public Ray {
  const bool insideMat;
  const int depth;
  LightRay(const glm::dvec4 &from, const glm::dvec4 &v, bool insideMat, int depth) :
    Ray(from, v), insideMat(insideMat), depth(depth)
  {}
};
