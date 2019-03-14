#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Constants.hpp"
#include "Log.hpp"
#include "Math.hpp"
#include "Scene.hpp"
#include "material/Material.hpp"
#include "node/Node.hpp"

#include <iostream>

using namespace std;

Scene::Scene(
  const Node *const root,
  const std::vector<const Light *> &lights,
  const glm::dvec3 &ambient)
    : root(root), lights(lights), ambientLight(ambient)
{
}

const LightRay
Scene::constructRay(int x, int y, int width, int height)
{
  glm::dvec4 from = constants::ORIGIN;
  float onWindowX = (float)x / width * 2 - 1;
  float onWindowY = (float)y / height * 2 - 1;

  const glm::dvec4 to(onWindowX, onWindowY, 1, 1);
  const int startingDepth = 3;
  return LightRay(
    from,
    to - from,
    false,
    startingDepth); // TODO
}

const Color
Scene::getColor(const LightRay &rayFromEye) const
{
  return Color(glm::dvec4(fireRay(rayFromEye), 1));
}

const glm::dvec3
Scene::fireRay(const LightRay &rayFromEye) const
{
  Log::debug(
    "firing ray {} {}",
    to_string(rayFromEye.from),
    to_string(rayFromEye.v));
  glm::dvec4 sceneHit; // A point
  glm::dvec4 sceneHitNormal;
  const Node *hitNode =
    root->intersect(rayFromEye, sceneHit, sceneHitNormal);

  const double distToHit =
    glm::distance(rayFromEye.from, sceneHit);
  if (hitNode == nullptr)
    return glm::dvec3(0);
  // if (distToHit < constants::EPSILON) return
  // glm::dvec3(0);
  Log::debug("hit {}", hitNode->name);

  return hitNode->getColor(
    *this, rayFromEye, sceneHit, sceneHitNormal);
}
