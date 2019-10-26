//
// Created by mllilek on 10/16/19.
//

#pragma once

#include <glm/geometric.hpp>

namespace maths {
  double distance3d(const glm::dvec3 &a, const glm::dvec3 &b);

  glm::vec3 traceRay(const glm::dvec3 &p, const glm::dvec3 &v, double t);

  bool allGt(const glm::dvec3 &v, double c);

  double normalizeDot3d(const glm::dvec3 &a, const glm::dvec3 &b);

  glm::vec3 halfwayVector3d(const glm::dvec3 &a, const glm::dvec3 &b);

  glm::dvec3 cross3d(const glm::dvec3 &a, const glm::dvec3 &b);
}

