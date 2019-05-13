#pragma once

#include "Point.hpp"
#include "Vector.hpp"
#include "Ray.hpp"

class Camera {
  Point eye;
  Vector up;
  Vector towards;
  int distanceFromEyeToScreen;
  int screenWidth;
  int screenHeight;

public:
  Camera(Point eye,
      Vector up,
      Vector towards,
      int screenWidth,
      int screenHeight);

  Ray getRayFromEyeToScreen(int i, int j) const;
};
