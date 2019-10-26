#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "Log.hpp"

Camera::Camera(
    const glm::dvec3 &eye,
    const glm::dvec3 &up,
    const glm::dvec3 &towards,
    int width, 
    int height,
    double fov) :
  eye(glm::dvec4(eye, 1.0)),
  up(glm::dvec4(up,0)),
  towards(glm::dvec4(towards, 0)),
  width(width),
  height(height)
{
  // 2d point on screen ([0,width],[0,height])->([-w/2,w/2],..,-1)
  const glm::dmat4x4 pointToScreen = glm::translate(glm::dmat4(1),
      glm::dvec3(-(width / 2), -(height / 2), -1));
  spdlog::debug("pointToScreen {}", pointToScreen);

  // Considers the fov, so will be between 0 and 2
  const double worldWindowHeight = 2 * glm::tan(glm::radians(fov) / 2);
  spdlog::debug("worldWindowHeight {}", worldWindowHeight);

  // Maintain the aspect ratio of the image
  const double worldWindowWidth = (width /  height) * worldWindowHeight;
  spdlog::debug("worldWindowWidth {}", worldWindowWidth);

  // scale it to the screen size in the world
  const glm::dmat4 screenToView = glm::scale(glm::dmat4(1), glm::dvec3(
        worldWindowWidth / width, -worldWindowHeight / height, 1));
  spdlog::debug("screenToView {}", screenToView);

  // lookAt gives world to view, we need inverse since going to world
  const glm::dmat4 viewToWorld = glm::inverse(
      glm::lookAt(glm::dvec3(eye), glm::dvec3(towards), glm::dvec3(up)));
  spdlog::debug("viewToWorld {}", viewToWorld);

  pointToWorld = viewToWorld * screenToView * pointToScreen;
  spdlog::debug("pointToWorld {}", pointToWorld);
}

Ray Camera::getRayFromEyeToScreen(int x, int y) const
{
  glm::dvec4 res(pointToWorld * glm::dvec4(x, y, 0, 1) - eye);
  Ray ray(eye, res);
  return ray;
}

