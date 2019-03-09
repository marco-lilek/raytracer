#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Scene.hpp"
#include "Math.hpp"
#include "Constants.hpp"
#include "material/Material.hpp"
#include "node/Node.hpp"
#include "Printglm.hpp"

#include <iostream>

using namespace std;

Scene::Scene(
             const Node * const root, 
             const std::vector<const Light *> &lights,
             const glm::dvec3 &ambient
             ) : 
  root(root), 
  lights(lights),
  ambientLight(ambient)
{}

const LightRay Scene::constructRay(int x, int y, int width, int height) {
  glm::dvec4 from = constants::ORIGIN;
  float onWindowX = (float)x / width * 2 - 1;
  float onWindowY = (float)y / height * 2 - 1;

  const glm::dvec4 to(onWindowX, onWindowY, 1, 1);
  const double startingRefractionIndex = 1;
  const int startingDepth = 2;
  return LightRay(from, to-from, startingRefractionIndex, startingDepth); // TODO
}

const Color Scene::getColor(const LightRay &rayFromEye) const {
  return Color(glm::dvec4(fireRay(rayFromEye), 1));
}

const glm::dvec3 Scene::fireRay(
    const LightRay &rayFromEye
                                ) const {
  glm::dvec4 sceneHit; // A point
  glm::dvec4 sceneHitNormal;
  const Node *hitNode = root->intersect(rayFromEye, sceneHit, sceneHitNormal);

  const double distToHit = glm::distance(rayFromEye.from, sceneHit);
  if (distToHit < constants::EPSILON) return glm::dvec3(0);
  if (hitNode == nullptr) return glm::dvec3(0);

  return hitNode->getColor(*this, rayFromEye, sceneHit, sceneHitNormal);

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
