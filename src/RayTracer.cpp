#include "RayTracer.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Printglm.hpp"
#include "RuntimeConfig.hpp"
#include "Debug.hpp"

#include <spdlog/spdlog.h>
#include <iostream>

using namespace std;

void RayTracer::render(
  const Node *rootNode,
  const std::vector<const Light *> &lights,
  const std::string &fname,
  const int width,
  const int height,
  //const glm::dvec3 &eye,
  //const glm::dvec3 &view,
  //double fovy,
  const glm::dvec3 &ambient
                       ) {
  cout << "Running with arguments" << endl
       << "lights " << lights.size() << endl
       << "fname " << fname << endl
       << "width " << width << endl
       << "height " << height << endl
       << "ambient " << ambient << endl
    ;

  // TODO move once luabridge fixed
  const Light l(glm::dvec3(1,1,1), glm::dvec3(0,0,0));
  std::vector<const Light *> llights;
  llights.push_back(&l);

  Image img(width, height);
  const Scene scene(rootNode, llights, ambient);

  int startX = 0;
  int startY = 0;
  int endX = img.width;
  int endY = img.height;

  if (rc::get().singlePixel) {
    spdlog::info("shooting single pixel");
    startX = img.width / 2;
    startY = img.height / 2;
    endX = img.width/2+1;
    endY = img.height/2+1;
  }

  for (int i = startX; i < endX; i++) {
    for (int j = startY; j < endY; j++) {
      spdlog::debug("############ PIXEL {} {}", i, j);
      const LightRay r = Scene::constructRay(i, j, img.width, img.height);
      const Color color = scene.getColor(r);
      img.drawPixel(i, j, color.r, color.g, color.b, color.a);
    }
  }

  img.render(fname);
  cout << "DONE" << endl;
}
