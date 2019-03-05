#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <loguru/loguru.hpp>

#include "Scene.hpp"
#include "Helpers.hpp"
#include "material/Material.hpp"
#include "node/Node.hpp"

#include <iostream>

using namespace std;

Scene::Scene(const Node * const root, 
  const std::vector<const Light *> &lights) : 
  root(root), 
  lights(lights)
{}

const Ray Scene::constructRay(int x, int y, int width, int height) {
  glm::dvec4 from = constants::ORIGIN;
  float onWindowX = (float)x / width * 2 - 1;
  float onWindowY = (float)y / height * 2 - 1;

  const glm::dvec4 to(onWindowX, onWindowY, 1, 1);

  const glm::dvec4 shift(0,0,-5,0);

  return Ray(from + shift, to - from);
}

const Color Scene::getColor(const Ray &rayFromEye) const {
  float numBounces = 2;
  return Color(glm::dvec4(fireRay(rayFromEye, numBounces - 1, 1), 1));
}

const glm::dvec3 Scene::fireRay(
    const Ray &rayFromEye,
    const int depth,
    const double curRefractionIndex) const {
  glm::dvec4 sceneHit; // A point
  glm::dvec4 sceneHitNormal;
  const Material *m = root->intersect(rayFromEye, sceneHit, sceneHitNormal);

  const double distToHit = glm::distance(rayFromEye.from, sceneHit);
  if (distToHit < constants::EPSILON) return glm::dvec3(0);
  if (m == nullptr) return glm::dvec3(0);

  return m->intersect(
      *this, rayFromEye, depth, curRefractionIndex, sceneHit, sceneHitNormal);

/*   finalColor = finalColor * (1 - m->reflectiveness); */

/*   if (depth > 0 && m->reflectiveness > 0) { // Skip the extra step if were not reflective */
/*     // This was a huge pain point: for the reflection to work correctly you need to normalize the normal */
/*     // and note we also don't normalize the incident/reflected vectors to avoid acc error */
/*     //cerr << "normal " << glm::to_string(sceneHitNormal) << endl; */
/*     //cerr << "incoming " << glm::to_string(rayFromEye.v) << endl; */
/*     //cerr << "relfectedDir " << glm::to_string(reflectedDir) << " " << glm::to_string(sceneHit) << endl; */
/*     //cerr << "angle " << glm::degrees(glm::angle(sceneHitNormal, rayFromEye.v)) << endl; */
/*     if (glm::dot(sceneHitNormal, rayFromEye.v) != 0) { // Perpendicular */
/*       const Ray reflectedRay(sceneHit, reflectedDir); */
/*       finalColor += fireRay(reflectedRay, depth-1) * m->reflectiveness; */
/*     } */
/*   } */

  //cerr << "finalColor " << glm::to_string(finalColor) << endl;
}
