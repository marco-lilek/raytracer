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
#include "PhongMaterial.hpp"
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
  // TODO parameterize
  int maxIterations = 3;

  return getColor(rayFromEye, maxIterations);
}

const Color
Scene::getColor(const Ray &rayFromEye, int depth) const
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
    return material->getColor(intersection.geometry.get()->shooterPos);
  }

  if (const PhongMaterial *material = 
      dynamic_cast<const PhongMaterial *>(intersection.hitNode->material)) {
    return getColorOfRayOnPhongMaterial(
        material, rayFromEye, *intersection.geometry.get());
  }

  if (const ReflectiveMaterial *material = 
      dynamic_cast<const ReflectiveMaterial *>(intersection.hitNode->material)) {
    return getColorOfRayOnReflectiveMaterial(
        material, rayFromEye, *intersection.geometry.get(), depth);
  }

  // TODO assert(0)
  // Should never be reached
  return Color(1,0,1); // #ff00ff
}

Color
Scene::getColorOfRayOnPhongMaterial(
    const PhongMaterial *material, 
    const Ray &rayFromEye,
    const GeometryIntersection &intersection) const {
  const char *METHOD_NAME = "Scene::getColorOfRayOnPhongMaterial";
  // TODO parameterize it
  const Color AMBIENT_LIGHT(0.2);

  Log::trace(METHOD_NAME, "material {}", *material);

  // This is the color ultimately returned from this method
  Color finalColor(0);

  {
    // To simplify just assume we have a constant ambient diffuse lighting
    // This light is always present even if we're in the shadow, which is why
    // we do this computation first
    Color ambientLight = AMBIENT_LIGHT * material->kd;
    Log::trace(METHOD_NAME, "ambientLight {}", ambientLight);
    CHECK(METHOD_NAME, ambientLight >= 0);
    finalColor += ambientLight;
  }

  // Compute the specular and diffuse lighting from each light source. 
  // Specifically, for each light source, we much cast a "shadow ray" 
  // from this point of intersection to the light.
  //
  // If this shadow ray intersects with another node in the scene, before it
  // reaches the light, then we know this light source does not illuminate this
  // point of intserection, and so we don't need to proceed with the rest
  // of the lighting calculation.
  for (int lightIdx = 0; lightIdx < lights.size(); lightIdx++) {
    const Light *light = lights[lightIdx];
    Log::trace(METHOD_NAME, "checking light{} {}", lightIdx, *light);

    const Point shooterPosOfShadow = intersection.p + intersection.n.normalize();

    // Ray from the point of intersection to the light
    const Ray shadowRay(shooterPosOfShadow, 
        light->pos - shooterPosOfShadow);
    Log::trace(METHOD_NAME, "shadowRay {}", shadowRay);

    // we still need some correction to prevent the case when we get an
    // obtuse angle between the normal and the shadow ray 
    // because of our "shift" by epsilon
    double shadowRayDotNormal = shadowRay.v.dot(intersection.n);
    if (shadowRayDotNormal < 0) {
      Log::trace(METHOD_NAME,
          "no illumiation because shadowRayDotNormal {} < 0, shadowRay {} normal {}",
          shadowRayDotNormal, shadowRay.v, intersection.n);
      continue;
    }

    {
      // Checking if the shadow ray reaches the light
      // if not, then we can skip the rest of the lighting calculation
      // for this light source
      const PhysicalIntersection &shadowRayIntersection = root->intersect(shadowRay);
      Log::trace(METHOD_NAME, "shadowRayIntersection {}", shadowRayIntersection);
      if (shadowRayIntersection.isHit()) {
        const GeometryIntersection &shadowRayGeometry = *shadowRayIntersection.geometry;
        // We intersected the scene, but it is still possible that 
        // we reach the light source before we hit the scene
        double lengthOfShadowRay = intersection.p.distanceTo(shadowRayGeometry.p);
        double distanceToLight = intersection.p.distanceTo(light->pos);
        Log::trace(METHOD_NAME, 
            "lengthOfShadowRay {} distanceToLight {}",
            lengthOfShadowRay, distanceToLight);
        if (lengthOfShadowRay < distanceToLight) {
          // Ah no we definitely intersected the scene before reaching the light
          // so this light does NOT illuminate our point of intersection
          continue;
        }
      }
    }

    // We know this light illuminates our point of intersection. 
    // So we can proceed with the rest of the lighting calculation
    Log::trace(METHOD_NAME, "light{} illuminates intersection.p {}", 
        lightIdx, intersection.p);

    {
      // Diffuse lighting is based on the angle between the normal
      // at the point of intersection and direction of the shadowRay
      double diffuseFactor = shadowRay.v.normalizeDot(intersection.n);
      Log::trace(METHOD_NAME, "diffuseFactor {}", diffuseFactor);

      const Color diffuseColor(diffuseFactor * material->kd * light->color);
      Log::trace(METHOD_NAME, "diffuseColor {}", diffuseColor);
      CHECK(METHOD_NAME, diffuseColor >= 0);
      finalColor += diffuseColor;
    }

    {
      // Specular lighting also factors in the angle between the normal
      // and the eye
      const Vector halfwayVector = shadowRay.v.halfwayVector(-rayFromEye.v);
      Log::trace(METHOD_NAME, "halfwayVector {}", halfwayVector);
      double hDotn = halfwayVector.normalizeDot(intersection.n);
      Log::trace(METHOD_NAME, "hDotn {}", hDotn);
      double specularFactor = glm::pow(hDotn, material->shininess);
      Log::trace(METHOD_NAME, "specularFactor {}", specularFactor);

      const Color specularColor(specularFactor * material->ks * light->color);
      Log::trace(METHOD_NAME, "specularColor {}", specularColor);
      CHECK(METHOD_NAME, specularColor >= 0);
      finalColor += specularColor;
    }

    Log::trace(METHOD_NAME, "after light{}, finalColor {}", 
        lightIdx, finalColor);
  }

  Log::trace(METHOD_NAME, "finalColor {}", finalColor);
  // TODO it is very possible our color exceeds 1, we need to add 
  // some safeguards to clamp its range so that it doesn't act up when
  // we convert it to bytes
  return finalColor.clamp();
}

Color Scene::getColorOfRayOnReflectiveMaterial(
    const ReflectiveMaterial *material, 
    const Ray &rayFromEye,
    const GeometryIntersection &intersection,
    const int depth) const {
  const char * METHOD_NAME = "Scene::getColorOfRayOnReflectiveMaterial";
  // A pure reflective material just returns the color from the reflected ray
  if (depth == 0) {
    // To avoid infinite recursion
    Log::trace(METHOD_NAME, "depth == 0, terminating");
    return Color(0);
  }

  Vector normalizedN = intersection.n.normalize();
  Ray reflectedRay(intersection.p + normalizedN, 
      rayFromEye.v.reflectAcross(normalizedN));
  Log::trace(METHOD_NAME, "depth {} reflectedRay {}", depth, reflectedRay);

  return getColor(reflectedRay, depth-1);
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

const char * Scene::type() const {
  return "Scene";
}

std::ostream& Scene::dump(std::ostream& o) const {
  // Dump the full node tree
  o << "nodeTree ";
  root->dumpNodeTree(o);

  o << "lights [";
  for (int i = 0; i < lights.size(); i++) {
    o << " light" << i << " " << *lights[i];
  }
  o << "]";
}
