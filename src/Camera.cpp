#include "Camera.hpp"
#include "Log.hpp"

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

Camera::Camera(Point eye,
    Vector up,
    Vector towards,
    int width, 
    int height,
    double fov) :
  eye(eye),
  up(up),
  towards(towards),
  width(width),
  height(height)
{
  const char *TRACE_HEADER = "Camera::Camera";
  // 2d point on screen ([0,width],[0,height])->([-w/2,w/2],..,-1)
  const dmat4 pointToScreen = glm::translate(dmat4(1), 
      glm::dvec3(-(width / 2), -(height / 2), -1));
  Log::debug(TRACE_HEADER, "pointToScreen {}", to_string(pointToScreen));

  // Considers the fov, so will be between 0 and 2
  const double worldWindowHeight = 2 * glm::tan(glm::radians(fov) / 2);
  Log::debug(TRACE_HEADER, "worldWindowHeight {}", worldWindowHeight);

  // Maintain the aspect ratio of the image
  const double worldWindowWidth = (width /  height) * worldWindowHeight;
  Log::debug(TRACE_HEADER, "worldWindowWidth {}", worldWindowWidth);

  // scale it to the screen size in the world
  const dmat4 screenToView = glm::scale(dmat4(1), dvec3(
        worldWindowWidth / width, -worldWindowHeight / height, 1));
  Log::debug(TRACE_HEADER, "screenToView {}", to_string(screenToView));

  // lookAt gives world to view, we need inverse since going to world
  const dmat4 viewToWorld = glm::inverse(
      glm::lookAt(dvec3(eye), dvec3(towards), dvec3(up)));
  Log::debug(TRACE_HEADER, "viewToWorld {}", to_string(viewToWorld));

  pointToWorld = viewToWorld * screenToView * pointToScreen;
  Log::debug(TRACE_HEADER, "pointToWorld {}", to_string(pointToWorld));
}

Ray Camera::getRayFromEyeToScreen(int x, int y) const
{
  return Ray(eye, dvec4(pointToWorld * glm::dvec4(x,y,0,1)) - eye); 
}

