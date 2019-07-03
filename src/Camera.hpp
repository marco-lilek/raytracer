#pragma once

#include "Glm.hpp"
#include "Ray.hpp"

struct Camera : public Object {
  Glm::Vec4 eye;
  Glm::Vec4 up;
  Glm::Vec4 towards;
  int width, height;
  double fov;
  Glm::Mat4 pointToWorld;

  Camera(
      const Glm::Vec3 &eye,
      const Glm::Vec3 &up,
      const Glm::Vec3 &towards,
      int width,
      int height,
      double fov);

  Ray getRayFromEyeToScreen(int, int) const;

  virtual const char * type() const {
    return "Camera";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << "eye " << eye << " up " << up << " towards " << towards;
  }
};
