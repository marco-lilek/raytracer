#include <iostream>

#include "node/GeometryNode.hpp"
#include "Primitive.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Light.hpp"

using namespace std;

int main() {
  cout << "it works!" << endl;
  Sphere s(1);
  GeometryNode g("cool", &s, Material(
    glm::vec3(0,0.5,0),
    glm::vec3(0,0,1), 10));
  g.scale(glm::vec3(2, 1,1));
  g.rotate('z', 45);

  const Light l(
    glm::vec3(1.0, 0.5, 0.5), 
    glm::vec4(0,5,-5, 1));
  
  std::vector<const Light *> lights;
  lights.push_back(&l);

  Image img(200, 200);
  Scene scene(&g, lights);

  for (int i = 0; i < img.width; i++) {
    for (int j = 0; j < img.width; j++) {
      Ray r = Scene::constructRay(i, j, img.width, img.height);
      Color color = scene.fireRay(r);
      img.drawPixel(i, j, color.r, color.g, color.b, color.a);
    }
  }

  img.render("result.png");
}
