#include "Math.hpp"
#include "Ray.hpp"
#include "Light.hpp"
#include "material/PhongMaterial.hpp"
#include "node/Node.hpp"

glm::dvec3 PhongMaterial::intersect(
  const Scene &scene,
  const Ray &rayFromEye,
  const int depth,
  const int curRefractionIndex,
  const glm::dvec4 &sceneHit,
  const glm::dvec4 &sceneHitNormal) const {
  glm::dvec3 finalColor(0);

  return glm::dvec3(1);
  finalColor += scene.ambientLight * kd;

  for (auto lightIt = scene.lights.begin(); lightIt != scene.lights.end(); ++lightIt) {
    const Light *light = *lightIt;
    const Ray rayToLight(sceneHit, light->pos - sceneHit);

    // //cerr << glm::to_string(rayToLight.v) << " " << glm::to_string(rayToLight.from) << endl;
    glm::dvec4 shadowHit;
    glm::dvec4 shadowHitNormal;
    const Material *intersectScene = scene.root->intersect(
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
      double diffuseFactor = math::normalizedDot(rayToLight.v, sceneHitNormal);
      /* //cerr << "diffuseFactor " << diffuseFactor << endl; */
      const glm::dvec3 diffuse(diffuseFactor * kd * light->color);
      finalColor += diffuse;
    }

    {
      // Specular lighting
      glm::dvec4 halfway = math::halfwayVector(rayToLight.v, -rayFromEye.v);
      double hDotn = math::normalizedDot(halfway, sceneHitNormal);
      double specularFactor = glm::pow(hDotn, shininess);
      /* //cerr << "specularFactor " << specularFactor << endl; */
      const glm::dvec3 specular(specularFactor * ks * light->color);
      finalColor += specular;
    }
  }

  return glm::min(glm::dvec3(finalColor), glm::dvec3(1));

/*   const glm::dvec4 reflectedDir = glm::reflect( */
/*       rayFromEye.v, glm::normalize(sceneHitNormal)); */
/*   const glm::dvec4 refractedDir = glm::refract( */
/*       glm::normalize(rayFromEye.v), */
/*       glm::normalize(sceneHitNormal), */
/*       curRefractionIndex / refractionIndex); */
/*   const double reflectionCoeff = Material::computeReflectionCoeff( */
/*       glm::angle(rayFromEye.v, sceneHitNormal), */ 
/*       curRefractionIndex, refractionIndex); */

}
