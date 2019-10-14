#include "UVSphere.hpp"

using namespace Glm;

Intersection *UVSphere::intersect(const Ray &incomingRay) const {
  GeometryIntersection *onSphere = Sphere::intersect(incomingRay);
  Vec3 y = Vec3(0,1,0);
  Vec3 tangent = glm::cross(y, onSphere->n);

  double u = 0.5 + glm::atan2(n.z, d.x) / 2 * glm::pi;
  double v = 0.5 - glm::asin(n.y) / glm::pi;

  UVIntersection *uvIntersection = new UVIntersection(
      onSphere->p, onSphere->n, tangent, u, v);
}
