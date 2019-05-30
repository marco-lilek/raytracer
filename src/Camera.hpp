#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

class Camera : public Object {
  Point eye;
  Vector up;
  Vector towards;

public:
  Camera(Point eye,
      Vector up,
      Vector towards);

  Ray getRayFromEyeToScreen(double, double) const;

  virtual const char * type() const {
    return "Camera";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << "eye " << eye << " up " << up << " towards " << towards;
  }
};
