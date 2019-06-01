#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

struct Camera : public Object {
  Point eye;
  Vector up;
  Vector towards;
  int width, height;
  double fov;
  glm::mat4 pointToWorld;

  Camera(Point eye,
      Vector up,
      Vector towards,
      int width,
      int height, double fov);

  Ray getRayFromEyeToScreen(int, int) const;

  virtual const char * type() const {
    return "Camera";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << "eye " << eye << " up " << up << " towards " << towards;
  }
};
