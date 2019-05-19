#include "Camera.hpp"

Camera::Camera(Point eye,
    Vector up,
    Vector towards,
    int screenWidth,
    int screenHeight) :
  eye(eye),
  up(up),
  towards(towards),
  screenWidth(screenWidth),
  screenHeight(screenHeight)
{}

Ray Camera::getRayFromEyeToScreen(int i, int j) const
{
  // 1. Compute the plane representing the screen in the 3d space
  // starting with the unit vector for the positive x direction
  Vector screenRight = towards.cross(up).normalize();

  // then the unit vector for the positive y direction
  Vector screenUp = towards.cross(screenRight).normalize();

  // 2. Compute the scale for these unit vectors based on the pixel
  // location on the screen

  // translating from [0-screenWidth] to (-1,1)
  double offsetRight = (double)i / screenWidth * 2 - 1;

  // same for the offset up
  double offsetUp = (double)j / screenHeight * 2 - 1;

  return Ray(eye,
      towards 
      + screenUp * offsetUp 
      + screenRight * offsetRight);
}

