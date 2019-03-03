#pragma once

#include <glm/glm.hpp>

struct Ray {
  const glm::dvec4 from;
  const glm::dvec4 v;

  Ray(const glm::dvec4 &from, const glm::dvec4 &v) : 
    from(from), v(v) {}

  static glm::dvec4 pointAt(const Ray &r, const double &t) {
    return r.from + r.v * t;
  }
};
