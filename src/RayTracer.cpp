#include "RayTracer.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "PrintGlm.hpp"

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
  cout << "Running with arguments"
       << "lights " << lights.size() << endl
       << "fname " << fname << endl
       << "width " << width << endl
       << "height " << height << endl
       << "ambient " << ambient << endl
    ;

  Image img(width, height);
  const Scene scene(rootNode, lights, ambient);

  int startX = 0;
  int startY = 0;
  int endX = img.width;
  int endY = img.height;

  for (int i = startX; i < endX; i++) {
    for (int j = startY; j < endY; j++) {
      //cerr << "############################pixel x " << i << " y " << j << endl;
      const Ray r = Scene::constructRay(i, j, img.width, img.height);
      const Color color = scene.getColor(r);
      img.drawPixel(i, j, color.r, color.g, color.b, color.a);
    }
  }

  img.render(fname);
  cout << "DONE" << endl;
}
