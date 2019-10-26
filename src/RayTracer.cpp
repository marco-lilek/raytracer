//
// Created by mllilek on 10/15/19.
//

#include "Log.hpp"
#include "RayTracer.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "RuntimeConfig.hpp"

void RayTracer::render(
        const Node *rootNode,
        Image &image,
        const glm::dvec3 &eye,
        const glm::dvec3 &view,
        const glm::dvec3 &up,
        const double &fov,
        const glm::dvec3 &ambient,
        const std::vector<const Light *> lights) {
  Camera camera(eye, up, view, image.width, image.height, fov);
  Scene scene(rootNode, lights, ambient);

  const RuntimeConfig &rc = RuntimeConfig::get();
  ViewWindow *vw = rc.viewWindow;
  int sx,sy,ex,ey;
  if (vw != nullptr) {
    sx = vw->x1;
    ex = vw->x2;
    sy = vw->y1;
    ey = vw->y2;
  } else {
    sx = 0; ex = image.width;
    sy = 0; ey = image.height;
  }
  for (int x = sx; x < ex; x++) {
    for (int y = sy; y < ey; y++) {
      Ray ray = camera.getRayFromEyeToScreen(x, y);
      spdlog::trace("x {} y {}", x, y);
      glm::dvec3 color = scene.getColor(ray);
      image.draw(color, x, y);
    }
  }

}

