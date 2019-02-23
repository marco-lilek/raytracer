#include <iostream>

#include "node/GeometryNode.hpp"
#include "Primitive.hpp"
#include "Image.hpp"
#include "Scene.hpp"

using namespace std;



int main() {
  cout << "it works!" << endl;
  Sphere s(1);
  GeometryNode g("cool", &s);
  Image img(200, 200);
  Scene scene(&g);

  for (int i = 0; i < img.width; i++) {
    for (int j = 0; j < img.width; j++) {
      Ray r = Scene::constructRay(i, j, img.width, img.height);
      Color color = scene.fireRay(r);
      img.drawPixel(i, j, color.r, color.g, color.b, color.a);
    }
  }

  img.render("result.png");
}
