#include "Sphere.hpp"
#include "Constants.hpp"
#include "Debug.hpp"
#include "Log.hpp"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <polyroots.hpp>

using namespace std;

GeometryIntersection Sphere::intersect(const Ray &incomingRay) const {
  const char * METHOD_NAME = "Sphere::intersect";
  Log::trace(METHOD_NAME, "incomingRay {}", incomingRay);
  
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
  // quadractic formula badaboobbadabing eh whats it take to get a coffe over here

  glm::dvec3 a(incomingRay.from);
  glm::dvec3 d(incomingRay.v);

  // The coefficients from above
  float A = glm::dot(d, d);
  float B = 2 * glm::dot(d, a);
  float C = glm::dot(a, a) - 1;

  double roots[2];
  size_t numRoots = quadraticRoots(A, B, C, roots);

  if (numRoots == 0) {
    // Total miss
    return GeometryIntersection(GeometryIntersection::Miss);
  }

  // For ray a + td, the closest t for which we intersect the sphere
  double t;

  if (numRoots == 1) {
    // Easy case
    float root = roots[0];
    
    // But still reject if its behind us
    if (root < constants::EPSILON) {
      return GeometryIntersection(GeometryIntersection::Past);
    }

    t = roots[0];
  }

  // Great we intersect twice, but the sphere could still be behind us
  GeometryIntersection::ShooterPos shooterPos;
  if (numRoots == 2) {
    float l, r;
    l = roots[0];
    r = roots[1];
    if (l < constants::EPSILON && r < constants::EPSILON) {
      // The whole sphere is behind us
      return GeometryIntersection(GeometryIntersection::Past);
    }
    if (l < constants::EPSILON || r < constants::EPSILON) {
      shooterPos = GeometryIntersection::Inside;
      // We're inside the sphere!
      t = glm::max(l, r);
    } else {
      shooterPos = GeometryIntersection::Towards;
      // The sphere is in front of us
      // So return the point of intersection closer to us
      t = glm::min(l, r);
    }
  }

  Point pointOfIntersection = incomingRay.pointAt(t);

  // Since we already assume the sphere is centered at 0,0,0, the normal
  // is the same as the point of intersection
  Vector normal = Vector(pointOfIntersection);

  return GeometryIntersection(shooterPos, 
      pointOfIntersection, normal);
}
