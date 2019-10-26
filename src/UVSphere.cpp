//
// Created by mllilek on 10/22/19.
//

#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
#include "UVSphere.hpp"

Intersection UVSphere::intersect(const Ray &incomingRay) const {
  Intersection intersection = Sphere::intersect(incomingRay);
  if (!intersection.isHit()) {
    return intersection;
  }

  glm::dvec3 d = -intersection.n;
  glm::dvec3 y = glm::dvec3(0,1,0);
  double atan = glm::atan(d.z, d.x);

  intersection.u = 0.5 + atan / (2 * glm::pi<double>());
  intersection.v = 0.5 - glm::asin(d.y) / glm::pi<double>();

  intersection.t = glm::dvec4(glm::cross(y, static_cast<glm::dvec3>(intersection.n)), 0.0);
  return intersection;
}
