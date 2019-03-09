#pragma once

#include "ray/Ray.hpp"

struct LightRay : public Ray {
  const double srcRefractionIdx;
  const int depth;
  LightRay(const glm::dvec4 &from, const glm::dvec4 &v, double srcRefractionIdx, int depth) :
    Ray(from, v), srcRefractionIdx(srcRefractionIdx), depth(depth)
  {}
};
