#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <loguru/loguru.hpp>

#include "Scene.hpp"
#include "Helpers.hpp"
#include "Material.hpp"
#include <iostream>

Scene::Scene(const Node * const root, 
  const std::vector<const Light *> &lights) : 
  root(root), 
  lights(lights), 
  ambientLight(glm::vec3(0)) {}

Ray Scene::constructRay(int x, int y, int width, int height) {
  glm::vec4 from = constants::POINT;
  float onWindowX = (float)x / width - 0.5;
  float onWindowY = (float)y / height - 0.5;

  glm::vec4 to(onWindowX, -onWindowY, 1, 1);

  glm::vec4 shift(0,0,5,0);

  return Ray(from - shift, to - from);
}

Color Scene::fireRay(const Ray &r) {
  glm::vec4 p; // A point
  glm::vec4 normal;
  const Material *m = root->intersect(r, p, normal);

  glm::vec3 finalColor = ambientLight; // Ambient lighting
  if (m) {
    for (auto lightIt = lights.begin(); lightIt != lights.end(); ++lightIt) {
      const Light *light = *lightIt;
      const Ray shadowRay(p, light->pos - p);
      glm::vec4 sceneHit;
      glm::vec4 dummyNormal; // Don't care about this one
      const Material *intersectScene = root->intersect(shadowRay, sceneHit, dummyNormal);
      if (intersectScene && 
        glm::distance(p, sceneHit) < glm::distance(light->pos, p)) {
        continue; // We hit something before reaching the light
      }

      // Diffuse lighting
      float diffuseFactor = helpers::normalizedDot(shadowRay.v, normal);
      glm::vec3 diffuse(diffuseFactor * m->kd);
      finalColor += diffuse;

      // Specular lighting
      glm::vec4 halfway = helpers::halfwayVector(shadowRay.v, r.v);
      float hDotn = helpers::normalizedDot(halfway, normal);
      float specularFactor = glm::pow(hDotn, m->shininess);
      glm::vec3 specular(specularFactor * m->ks);
      finalColor += specular;
    }
  }

  return Color(glm::vec4(finalColor,1));
}