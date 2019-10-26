#pragma once

#include <glm/detail/type_vec.hpp>
#include <glm/vec4.hpp>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "Ray.hpp"

struct Camera {
  glm::dvec4 eye;
  glm::dvec4 up;
  glm::dvec4 towards;
  int width, height;
  double fov;
  glm::dmat4 pointToWorld;

  Camera(
      const glm::dvec3 &eye,
      const glm::dvec3 &up,
      const glm::dvec3 &towards,
      int width,
      int height,
      double fov);

  Ray getRayFromEyeToScreen(int x, int y) const;
};
