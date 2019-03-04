#include "RayTracer.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Light.hpp"

void RayTracer::render(const Node *rootNode) {

  const Light l(
    glm::dvec3(0.5, 0.5, 0.5), 
    glm::dvec4(0,0,-3, 1));
  
  std::vector<const Light *> lights;
  lights.push_back(&l);

  Image img(200, 200);
  const Scene scene(rootNode, lights);

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

  img.render("result.png");
}
