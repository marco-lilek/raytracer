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
  ambientLight(glm::vec3(0.1)) {}

const Ray Scene::constructRay(int x, int y, int width, int height) {
  glm::vec4 from = constants::POINT;
  float onWindowX = (float)x / width - 0.5;
  float onWindowY = (float)y / height - 0.5;

  const glm::vec4 to(onWindowX, onWindowY, 1, 1);

  const glm::vec4 shift(0,0,-5,0);

  return Ray(from + shift, to - from);
}

const Color Scene::getColor(const Ray &rayFromEye) const {
  float numBounces = 2;
  return Color(glm::vec4(fireRay(rayFromEye, numBounces - 1), 1));
}

const glm::vec3 Scene::fireRay(const Ray &rayFromEye, const int depth) const {
  glm::vec4 sceneHit; // A point
  glm::vec4 sceneHitNormal;
  const Material *m = root->intersect(rayFromEye, sceneHit, sceneHitNormal);


  glm::vec3 finalColor(0);
  if (m == nullptr) return finalColor;

  finalColor += ambientLight * m->kd;

  for (auto lightIt = lights.begin(); lightIt != lights.end(); ++lightIt) {
    const Light *light = *lightIt;
    const Ray rayToLight(sceneHit, light->pos - sceneHit);

    glm::vec4 shadowHit;
    glm::vec4 shadowHitNormal;
    const Material *intersectScene = root->intersect(
      rayToLight, shadowHit, shadowHitNormal);
    if (intersectScene) {
      float lengthOfShadowRay = glm::distance(sceneHit, shadowHit);
      if (lengthOfShadowRay < glm::distance(light->pos, sceneHit)) {
        continue; // We hit something before reaching the light
      }
    }


    // Diffuse lighting
    float diffuseFactor = helpers::normalizedDot(rayToLight.v, sceneHitNormal);
    const glm::vec3 diffuse(diffuseFactor * m->kd);
    finalColor += diffuse;

    // Specular lighting
    glm::vec4 halfway = helpers::halfwayVector(rayToLight.v, -rayFromEye.v);
    float hDotn = helpers::normalizedDot(halfway, sceneHitNormal);
    float specularFactor = glm::pow(hDotn, m->shininess);
    const glm::vec3 specular(specularFactor * m->ks);
    //finalColor += specular;
  }

  if (depth > 0) {
    // This was a huge pain point: for the reflection to work correctly you need to normalize the normal
    // and note we also don't normalize the incident/reflected vectors to avoid acc error
    const glm::vec4 reflectedDir = glm::reflect(rayFromEye.v, glm::normalize(sceneHitNormal));
    const Ray reflectedRay(sceneHit, reflectedDir);

    glm::vec3 reflectedColor = fireRay(reflectedRay, depth - 1);
    finalColor += reflectedColor;
  }

  return glm::min(glm::vec3(finalColor), glm::vec3(1));
}