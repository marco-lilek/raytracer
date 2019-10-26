//
// Created by mllilek on 10/15/19.
//

#include <glm/glm.hpp>
#include <polyroots/polyroots.hpp>
#include "Sphere.hpp"
#include "maths.hpp"
#include "constants.hpp"

Intersection Sphere::intersect(const Ray &incomingRay) const {
  Intersection intersection;

  // Intersecting with a sphere centered at 0,0,0 with radius 1
  // then for any point on the sphere (x,y,z) we have
  // x^2 + y^2 + z^2 = 1^2
  //
  // intersecting with a ray: a + td
  // sub then solve for t
  //
  // (a.x+td.x)^2 + (a.y+td.y)^2 + (a.z+td.z)^2 = 1
  // a.x^2 + 2a.xtd.x + t^2d.x^2 ... = 1
  // t^2(d.x^2 + d.y^2 + d.z^2) + 2t(a.x*d.x + a.y*d.y ..) + dot(a,a) - 1 = 0
  // t^2 dot(d,d) + t 2dot(a,d) + (dot(a,a) - 1) = 0
  // quadractic formula badaboombadabing

  glm::vec3 a(incomingRay.p);
  glm::vec3 d(incomingRay.v);

  // The coefficients as described in the comment above
  float A = glm::dot(d, d);
  float B = 2 * glm::dot(d, a);
  float C = glm::dot(a, a) - 1;

  double roots[2];
  size_t numRoots = quadraticRoots(A, B, C, roots);

  if (numRoots == 0) {
    intersection.type = Intersection::CompleteMiss;
    return intersection;
  }

  // For ray a + td, the closest t for which we intersect the sphere
  double t;

  if (numRoots == 1) {
    // Easy case
    float root = roots[0];

    // But still reject if its behind us
    if (root < 0) {
      intersection.type = Intersection::ObjectBehindRay;
      return intersection;
    }

    t = roots[0];
  }

  // Great we intersect twice, but the sphere could still be behind us
  if (numRoots == 2) {
    float l, r;
    l = roots[0];
    r = roots[1];
    if (l < 0 && r < 0) {
      intersection.type = Intersection::ObjectBehindRay;
      // The whole sphere is behind us
    } else if (l < 0 || r < 0) {
      // One of the points of intersections in certainly behind us
      intersection.type = Intersection::RayInsideObject;
      // We're inside the sphere!
      t = glm::max(l, r);
    } else {
      intersection.type = Intersection::RayHitsObject;
      // The sphere is in front of us
      // So return the point of intersection closer to us
      t = glm::min(l, r);
    }
  }

  if (t < constants::EPSILON) {
    intersection.type = Intersection::CompleteMiss;
    return intersection;
  }

  glm::dvec3 poi(maths::traceRay(incomingRay.p, incomingRay.v, t));

  // Since we already assume the sphere is centered at 0,0,0, the normal
  // is the same as the point of intersection

  intersection.p = glm::dvec4(poi, 1.0);
  intersection.n = glm::dvec4(poi, 0.0);
  return intersection;
}
