#include "Scene.hpp"
#include "Helpers.hpp"

Scene::Scene(const Node * const root, 
  const std::vector<const Light *> &lights) : 
  root(root), lights(lights) {}

Ray Scene::constructRay(int x, int y, int width, int height) {
  glm::vec4 from = constants::POINT;
  float onWindowX = (float)x / width - 0.5;
  float onWindowY = (float)y / height - 0.5;

  glm::vec4 to(onWindowX, onWindowY, 1, 1);

  glm::vec4 shift(0,0,5,0);

  return Ray(from - shift, to - from);
}

Color Scene::fireRay(const Ray &r) {
  glm::vec4 p;
  glm::vec4 normal;
  if (root->intersect(r, p, normal)) {
    return Color(1);
  } else {
    return Color(glm::vec4(0,0,0,1));
  }
}