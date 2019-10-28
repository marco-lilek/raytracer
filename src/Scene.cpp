// Created by mllilek on 10/19/19.
//

#include <spdlog/spdlog.h>
#include <glm/gtx/vector_angle.hpp>

#include "Scene.hpp"
#include "DebugMaterial.hpp"
#include "PhongMaterial.hpp"
#include "maths.hpp"
#include "GeometryNode.hpp"
#include "Texture.hpp"
#include "MirrorMaterial.hpp"

Scene::Scene(
        const Node *const root,
        const std::vector<const Light *> lights,
        const glm::dvec3 &ambient) :
        root(root),
        lights(lights),
        globalIllumination(ambient) {}

glm::dvec3 Scene::getColor(const Ray &r) {
  int maxIterations = 4;

  return getColor(r, maxIterations);
}

glm::dvec3 Scene::getColor(const Ray &r, int depth) const {
  if (depth == 0) {
    return glm::dvec3(0);
  }

  const Intersection intersection(root->intersect(r));

  if (!intersection.isHit()) {
    return glm::dvec3(0);
  }

  // A node/its material is just a component of the state of the scene;
  // it does not make sense for a node/material to handle the lighting calculation
  // since these objects are unaware of the rest of the scene (namely other nodes,
  // light sources). For this reason we do the following dynamic_cast, if chain
  // block on the type of material we hit---the scene should be responsible for
  // the lighting calculation since its the only object which knows enough to be
  // able to do it.

  if (const DebugMaterial *material =
          dynamic_cast<const DebugMaterial *>(intersection.node->m)) {
    return material->color;
  }

  if (const PhongMaterial *material =
          dynamic_cast<const PhongMaterial *>(intersection.node->m)) {
    return getColorOfRayOnPhongMaterial(material, r, intersection);
  }

  // Recursive interacions need to pass on
  // depth
  // indexOfRefraction
  if (const MirrorMaterial *material =
          dynamic_cast<const MirrorMaterial *>(intersection.node->m)) {
    return getColorOfRayOnMirror(material, r, intersection, depth);
  }

  /*
  if (const RefractiveMaterial *material =
          dynamic_cast<const RefractiveMaterial *>(intersection.hitNode->material)) {
    return getColorOfRayOnRefractiveMaterial(
            material, rayFromEye, *intersection.geometry.get(), depth, media);
  }
  */

  assert(0); // fail
  return glm::dvec3(1,0,1); // #ff00ff
}


glm::dvec3 Scene::getColorOfRayOnMirror(
        const MirrorMaterial *material,
        const Ray &rayFromEye,
        const Intersection &intersection,
        const int depth) const {
  double angle = maths::angle3d(intersection.n, rayFromEye.v);
  Ray reflectedRay(intersection.p,
          glm::dvec4(maths::reflect3d(rayFromEye.v, intersection.n), 0.0));
  return getColor(reflectedRay, depth-1);
}

glm::dvec3
Scene::getColorOfRayOnPhongMaterial(
        const PhongMaterial *material,
        const Ray &rayFromEye,
        const Intersection &intersection) const {
  // This is the color ultimately returned from this method
  glm::dvec3 finalColor(0);

  {
    // To simplify just assume we have a constant ambient diffuse lighting
    // This light is always present even if we're in the shadow, which is why
    // we do this computation first
    glm::dvec3 ambientLight = globalIllumination * material->kd;
    assert(maths::allGt(ambientLight, 0));
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
    const glm::dvec4 shooterPosOfShadow = intersection.p;

    // Ray from the point of intersection to the light
    const Ray shadowRay(
            shooterPosOfShadow,
            glm::dvec4(light->position, 1) - shooterPosOfShadow);

    {
      // Checking if the shadow ray reaches the light
      // if not, then we can skip the rest of the lighting calculation
      // for this light source
      const Intersection shadowRayIntersection = root->intersect(shadowRay);
      if (shadowRayIntersection.isHit()) {
        // We intersected the scene, but it is still possible that
        // we reach the light source before we hit the scene
        double lengthOfShadowRay = maths::distance3d(
                intersection.p, shadowRayIntersection.p);
        double distanceToLight = maths::distance3d(intersection.p, light->position);
        if (lengthOfShadowRay < distanceToLight) {
          // Ah no we definitely intersected the scene before reaching the light
          // so this light does NOT illuminate our point of intersection
          continue;
        }
      }
    }

    // We know this light illuminates our point of intersection.
    // So we can proceed with the rest of the lighting calculation

    glm::dvec3 textureColor(1);
    glm::dvec4 normalForLighting = intersection.n;

    // We only do bump/texture mapping for uv intersections
    if (intersection.node->isUV()) {
      double u = intersection.u;
      double v = intersection.v;

      // TODO also support textures
      Material *m = intersection.node->m;

      // Do bump mapping
      Texture *bump = intersection.node->bump;
      if (bump != nullptr) {
        glm::dvec3 normalInTangentSpace = normalize(bump->getValue(u, v));
        glm::dvec4 bitangent = glm::dvec4(maths::cross3d(intersection.n, intersection.t),0.0);
        glm::dmat3 worldToTangentSpace = glm::dmat3(
                glm::dvec3(bitangent),
                glm::dvec3(intersection.t),
                glm::dvec3(intersection.n));
        normalForLighting = glm::dvec4(worldToTangentSpace * normalInTangentSpace, 0);
      }
    }

    {
      // Diffuse lighting is based on the angle between the normal
      // at the point of intersection and direction of the shadowRay
      double diffuseFactor = maths::normalizeDot3d(shadowRay.v, normalForLighting);

      const glm::dvec3 diffuseColor(
              diffuseFactor * material->kd * light->colour * textureColor);
      finalColor += glm::clamp(diffuseColor, 0.0, 1.0);
    }

    {
      // Specular lighting also factors in the angle between the normal
      // and the eye
      const glm::dvec4 halfwayVector = glm::dvec4(maths::halfwayVector3d(
              shadowRay.v, -rayFromEye.v), 0.0);
      double hDotn = maths::normalizeDot3d(halfwayVector, normalForLighting);
      double specularFactor = glm::pow(hDotn, material->shininess);

      const glm::dvec3 specularColor(
              specularFactor * material->ks * light->colour * textureColor);
      finalColor += glm::clamp(specularColor, 0.0, 1.0);
    }
  }

  // TODO it is very possible our color exceeds 1, we need to add
  // some safeguards to clamp its range so that it doesn't act up when
  // we convert it to bytes
  return glm::clamp(finalColor, 0.0, 1.0);
}

