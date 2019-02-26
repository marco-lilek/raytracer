#include <iostream>
#include <glm/gtx/string_cast.hpp>

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
    glm::vec3(0,0,0.5), 10));
  //g.scale(glm::vec3(2, 1,1));
  //g.rotate('z', 45);
  g.translate(glm::vec3(0,-1,0));

  GeometryNode g2("verycool", &s, Material(
    glm::vec3(0.5,0,0.5),
    glm::vec3(0,0,1), 10));
  g2.translate(glm::vec3(-1,1,0));

  GeometryNode g3("2cool", &s, Material(
    glm::vec3(0.5,0,0),
    glm::vec3(0,0,1), 10));
  g3.scale(glm::vec3(0.5,0.5,0.5));
  g3.translate(glm::vec3(1,0,-1.5));

  const Light l(
    glm::vec3(1.0, 0.5, 0.5), 
    glm::vec4(0,0,-3, 1));
  
  std::vector<const Light *> lights;
  lights.push_back(&l);

  Node root("sick");
  root.addChildren(&g);
  root.addChildren(&g2);
  root.addChildren(&g3);

  Image img(200, 200);
  const Scene scene(&root, lights);

  // int startX = 129;
  // int startY = 102;
  // int endX = 130;
  // int endY = 104;

  int startX = 0;
  int startY = 0;
  int endX = img.width;
  int endY = img.height;
  for (int i = startX; i < endX; i++) {
    for (int j = startY; j < endY; j++) {
      // cerr << "pixel x " << i << " y " << j << endl;
      const Ray r = Scene::constructRay(i, j, img.width, img.height);
      const Color color = scene.getColor(r);
      img.drawPixel(i, j, color.r, color.g, color.b, color.a);
    }
  }

  //glm::vec3 res = q * glm::vec2(1,0);
  // cerr << "res " << to_string(q) << to_string(res) << endl;

  img.render("result.png");
}
