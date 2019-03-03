#include <iostream>
#include <glm/gtx/string_cast.hpp>

#include "node/GeometryNode.hpp"
#include "primitive/Sphere.hpp"
#include "Image.hpp"
#include "Scene.hpp"
#include "Light.hpp"

using namespace std;
using namespace glm;

int main() {
  cout << "it works!" << endl;
  Sphere s(1);
  GeometryNode g("green one", &s, Material(
    glm::dvec3(0,0.5,0),
    glm::dvec3(0,0,0.5), 10));
  //g.scale(glm::dvec3(2, 1,1));
  //g.rotate('z', 45);
  g.translate(glm::dvec3(0,-1,0));

  GeometryNode g2("purple one", &s, Material(
    glm::dvec3(0.5,0,0.5),
    glm::dvec3(0,0,1), 10));
  g2.translate(glm::dvec3(-1,1,-1));

  GeometryNode g3("red one", &s, Material(
    glm::dvec3(0.5,0,0),
    glm::dvec3(0,0,1), 10));
  g3.scale(glm::dvec3(0.5,0.5,0.5));
  g3.translate(glm::dvec3(1,0,-1.5));

  GeometryNode g4("yellow big one", &s, Material(
    glm::dvec3(0.5,0.5,0),
    glm::dvec3(0,1,1), 10));
  g4.scale(glm::dvec3(10,10,1));
  g4.translate(glm::dvec3(0,0,-10));

  const Light l(
    glm::dvec3(0.5, 0.5, 0.5), 
    glm::dvec4(0,0,-3, 1));
  
  std::vector<const Light *> lights;
  lights.push_back(&l);

  Node root("sick");
  root.addChildren(&g);
  root.addChildren(&g2);
  root.addChildren(&g3);
  root.addChildren(&g4);

  Image img(200, 200);
  const Scene scene(&root, lights);

  /* int startX = 99; */
  /* int startY = 100; */
  /* int endX = startX+2; */
  /* int endY = startY+1; */

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

  /* vec4 a(-0.081634, 0.262385, 0.962154, 0.000000); */
  /* vec4 ap(-0.170163, -0.024309, -0.138201, 1.000000); */

  /* vec4 b(-0.077597, 0.315105, 0.946368, 0.000000); */
  /* vec4 bp(-0.145092, -0.024182, -0.163593, 1.000000); */

  /* scene.getColor(Ray(ap, a)); */
  /* scene.getColor(Ray(bp, b)); */


  //glm::dvec3 res = q * glm::vec2(1,0);
  // //cerr << "res " << to_string(q) << to_string(res) << endl;

  img.render("result.png");
}
