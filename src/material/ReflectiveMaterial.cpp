#include "ReflectiveMaterial.hpp"
#include <glm/gtx/vector_angle.hpp>
#include <cmath>
#include "Debug.hpp"
#include "Constants.hpp"

using namespace std;

namespace {

const double computeReflectionCoeff(
                                    double angle,
                                    double inRefrIdx,
                                    double outRefrIdx
                                    )
{
  spdlog::debug("angle for schlick {}", angle);
  // Based on Schlick's approximation
  double refrIdxRatio =
    (inRefrIdx - outRefrIdx) /
    (inRefrIdx + outRefrIdx);
  double R0 = pow(refrIdxRatio, 2.0);
  spdlog::debug("R0 {}", R0);
  double Rtheta = R0 + (1-R0) * pow(1 - abs(cos(angle)), 5.0);
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
  glm::dvec3 finalColor(0);

  spdlog::debug("hit the reflective");
  spdlog::debug("depth is {}", rayFromEye.depth);
  if (rayFromEye.depth <= 0) {
    return finalColor;
  }

  const bool incomingInsideMat = rayFromEye.insideMat;

  // TODO: come up with a better way to do this
  const double incomingRefrIdx = incomingInsideMat ? refractionIndex : 1.0;
  const double outgoingRefrIdx = incomingInsideMat ? 1.0 : refractionIndex;
  spdlog::debug("outgoingRefrIdx {} incomingRefrIdx {}", outgoingRefrIdx, incomingRefrIdx);

  const glm::dvec4 adjNormalAtHit = sceneHitNormal * (incomingInsideMat ? -1.0 : 1.0);

  const float reflectionCoeff = computeReflectionCoeff(
      glm::angle(rayFromEye.v, adjNormalAtHit), 
      incomingRefrIdx,
      outgoingRefrIdx
                                                        );
  spdlog::debug("reflectionCoeff {}", reflectionCoeff);
  assert(reflectionCoeff >= 0.0-constants::EPSILON &&
         reflectionCoeff <= 1.0 + constants::EPSILON);

  const glm::dvec4 reflectedDir = glm::reflect(
      rayFromEye.v, glm::normalize(adjNormalAtHit));
  const LightRay reflectedRay(sceneHit, reflectedDir, incomingInsideMat, rayFromEye.depth - 1);
  spdlog::debug("reflectedRay {} {}", to_string(reflectedRay.from), to_string(reflectedRay.v));
  glm::vec3 reflectedColor = scene.fireRay(reflectedRay);
  spdlog::debug("reflectedColor {}", to_string(reflectedColor));

  finalColor += reflectionCoeff * reflectedColor;

  if (outgoingRefrIdx < incomingRefrIdx) {
    const double criticalAngle = glm::asin(outgoingRefrIdx / incomingRefrIdx);
    const double incomingAngle = glm::angle(rayFromEye.v, -adjNormalAtHit);
    spdlog::debug("criticalAngle {} incomingAngle {}",
                  to_string(criticalAngle),
                  to_string(incomingAngle));
    if (incomingAngle > criticalAngle) {
      spdlog::debug("total internal refraction, finalColor {}", to_string(finalColor));
      return finalColor;
    }
  }

  const glm::dvec4 refractedDir = glm::refract(
      glm::normalize(rayFromEye.v),
      glm::normalize(adjNormalAtHit),
      incomingRefrIdx / outgoingRefrIdx
                                               );
  const LightRay refractedRay(sceneHit, refractedDir, !incomingInsideMat, rayFromEye.depth - 1);
  spdlog::debug("refractedRay {} {}", to_string(refractedRay.from), to_string(refractedRay.v));
  
  glm::vec3 refractedColor = scene.fireRay(refractedRay);
  spdlog::debug("refractedColor {}", to_string(refractedColor));

  finalColor += (1-reflectionCoeff) * refractedColor;
  spdlog::debug("finalColor {}", to_string(finalColor));

  return finalColor;
};
