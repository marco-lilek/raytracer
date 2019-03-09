#include "ReflectiveMaterial.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <cmath>

using namespace std;

namespace {

const double computeReflectionCoeff(
                                    double angle,
                                    double inRefrIdx,
                                    double outRefrIdx
                                    ) {
  // Based on Schlick's approximation
  double refrIdxRatio =
    (inRefrIdx - outRefrIdx) /
    (inRefrIdx + outRefrIdx);
  double R0 = pow(refrIdxRatio, 2.0);
  double Rtheta = R0 + (1-R0) * pow(1 - cos(angle), 5.0);
  return Rtheta;
}

} // namespace

glm::dvec3 ReflectiveMaterial::intersect(
  const Scene &scene,
  const LightRay &rayFromEye,
  const glm::dvec4 &sceneHit,
  const glm::dvec4 &sceneHitNormal
                            ) const 
{
  if (rayFromEye.depth > 0) {
    return glm::dvec3(0);
  }
  const glm::dvec4 reflectedDir = glm::reflect(
      rayFromEye.v, glm::normalize(sceneHitNormal));
  const glm::dvec4 refractedDir = glm::refract(
      glm::normalize(rayFromEye.v),
      glm::normalize(sceneHitNormal),
      rayFromEye.srcRefractionIdx / refractionIndex);
  const double reflectionCoeff = computeReflectionCoeff(
      glm::angle(rayFromEye.v, sceneHitNormal), 
      rayFromEye.srcRefractionIdx, refractionIndex);

  glm::vec3 reflectedColor = scene.fireRay(LightRay(sceneHit, reflectedDir, refractionIndex, rayFromEye.depth - 1));

  return reflectedColor;
                         
};
