#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <loguru/loguru.hpp>

#include "Scene.hpp"
#include "Helpers.hpp"
#include "Material.hpp"
#include <iostream>

using namespace std;

Scene::Scene(const Node * const root, 
  const std::vector<const Light *> &lights) : 
  root(root), 
  lights(lights), 
  ambientLight(glm::dvec3(0.5)) {}

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
  return Color(glm::dvec4(fireRay(rayFromEye, numBounces - 1), 1));
}

const glm::dvec3 Scene::fireRay(const Ray &rayFromEye, const int depth) const {
  glm::dvec4 sceneHit; // A point
  glm::dvec4 sceneHitNormal;
  const Material *m = root->intersect(rayFromEye, sceneHit, sceneHitNormal);
  glm::dvec3 finalColor(0);

  const double distToHit = glm::distance(rayFromEye.from, sceneHit);
  if (distToHit < constants::EPSILON) return finalColor;
  if (m == nullptr) return finalColor;

  if (true) {

    finalColor += ambientLight * m->kd;

    for (auto lightIt = lights.begin(); lightIt != lights.end(); ++lightIt) {
      const Light *light = *lightIt;
      const Ray rayToLight(sceneHit, light->pos - sceneHit);

      // //cerr << glm::to_string(rayToLight.v) << " " << glm::to_string(rayToLight.from) << endl;
      glm::dvec4 shadowHit;
      glm::dvec4 shadowHitNormal;
      const Material *intersectScene = root->intersect(
        rayToLight, shadowHit, shadowHitNormal);
      if (intersectScene) {
        // //cerr << glm::to_string(shadowHit) << endl;
        double lengthOfShadowRay = glm::distance(sceneHit, shadowHit);
        double distanceToLight = glm::distance(light->pos, sceneHit);
        if (lengthOfShadowRay < distanceToLight) {
          continue; // We hit something before reaching the light
        }
      }

      {
        // Diffuse lighting
        double diffuseFactor = helpers::normalizedDot(rayToLight.v, sceneHitNormal);
        /* //cerr << "diffuseFactor " << diffuseFactor << endl; */
        const glm::dvec3 diffuse(diffuseFactor * m->kd * light->color);
        finalColor += diffuse;
      }

      {
        // Specular lighting
        glm::dvec4 halfway = helpers::halfwayVector(rayToLight.v, -rayFromEye.v);
        double hDotn = helpers::normalizedDot(halfway, sceneHitNormal);
        double specularFactor = glm::pow(hDotn, m->shininess);
        /* //cerr << "specularFactor " << specularFactor << endl; */
        const glm::dvec3 specular(specularFactor * m->ks * light->color);
        finalColor += specular;
      }

    }
  }

  if (depth > 0) {
    // This was a huge pain point: for the reflection to work correctly you need to normalize the normal
    // and note we also don't normalize the incident/reflected vectors to avoid acc error
    const glm::dvec4 reflectedDir = glm::reflect(rayFromEye.v, glm::normalize(sceneHitNormal));
    //cerr << "normal " << glm::to_string(sceneHitNormal) << endl;
    //cerr << "incoming " << glm::to_string(rayFromEye.v) << endl;
    //cerr << "relfectedDir " << glm::to_string(reflectedDir) << " " << glm::to_string(sceneHit) << endl;
    //cerr << "angle " << glm::degrees(glm::angle(sceneHitNormal, rayFromEye.v)) << endl;
    if (glm::dot(sceneHitNormal, rayFromEye.v)) {

      const Ray reflectedRay(sceneHit, reflectedDir);
      finalColor += fireRay(reflectedRay, depth-1);

    }
    //cerr << "bitchass" << std::abs(glm::angle(glm::normalize(sceneHitNormal), glm::normalize(rayFromEye.v))-90) << endl;
  }

  //cerr << "finalColor " << glm::to_string(finalColor) << endl;

  return glm::min(glm::dvec3(finalColor), glm::dvec3(1));
}
