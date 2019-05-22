#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Constants.hpp"
#include "Log.hpp"
#include "Math.hpp"
#include "Scene.hpp"
#include "Material.hpp"
#include "Node.hpp"
#include "DebugMaterial.hpp"
#include "PhysicalNode.hpp"

#include <iostream>

using namespace std;

Scene::Scene(
  const Node *const root,
  const std::vector<const Light *> &lights,
  const glm::dvec3 &ambient)
    : root(root), lights(lights), ambientLight(ambient)
{
}

Scene::Scene(
  const Node *const root,
  const std::vector<const Light *> &lights) 
    : root(root), lights(lights)
{}

// const LightRay
// Scene::constructRay(int x, int y, int width, int height)
// {
//   glm::dvec4 from = constants::ORIGIN;
//   float onWindowX = (float)x / width * 2 - 1;
//   float onWindowY = (float)y / height * 2 - 1;
//   const glm::dvec4 to(onWindowX, onWindowY, 1, 1);
//   const int startingDepth = 3;
//   return LightRay(
//     from,
//     to - from,
//     false,
//     startingDepth); // TODO
// }

const Color
Scene::getColor(const Ray &rayFromEye) const
{
  const char *METHOD = "Scene::getColor";
  Log::trace(METHOD, "rayFromEye: {}", rayFromEye);
  const PhysicalIntersection intersection(root->intersect(rayFromEye));
  
  Log::trace(METHOD, "intersection: {}", intersection);
  if (!intersection.isHit()) {
    return Color(0);
  }

  // A node/its material is just a component of the state of the scene;
  // it does not make sense for a node/material to handle the lighting calculation
  // since these objects are unaware of the rest of the scene (namely other nodes,
  // light sources). For this reason we do the following dynamic_cast, if chain
  // block on the type of material we hit---the scene should be responsible for 
  // the lighting calculation since its the only object which knows enough to be 
  // able to do it.

  if (const DebugMaterial *material = 
      dynamic_cast<const DebugMaterial *>(intersection.hitNode->material)) {
    return material->getColor(intersection.geometry.shooterPos);
  }

  // TODO assert(0)
  // Should never be reached
  return Color(1,0,1); // #ff00ff
}

// const Intersection
// Scene::fireRay(const LightRay &rayFromEye) const
// {
//   string LOCATION = "Scene::fireRay";
//   Log::debug(LOCATION, "rayFromEye {}", rayFromEye);

//   glm::dvec4 sceneHit; // A point
//   glm::dvec4 sceneHitNormal;
//   const Node *hitNode = root->intersect(
//       rayFromEye, sceneHit, sceneHitNormal);

//   const double distToHit = glm::distance(
//       rayFromEye.from, sceneHit);
//   if (hitNode == nullptr)
//     return glm::dvec3(0);
//   Log::debug("hit {}", hitNode->name);

//   return hitNode->getColor(
//     *this, rayFromEye, sceneHit, sceneHitNormal);
// }
