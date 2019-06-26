#include "Sphere.hpp"
#include "Constants.hpp"
#include "Debug.hpp"
#include "Log.hpp"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <polyroots.hpp>
#include "GeometryIntersection.hpp"

using namespace std;

Intersection *Sphere::intersect(const Ray &incomingRay) const {
  const char * METHOD_NAME = "Sphere::intersect";
  
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
  // quadractic formula badaboombadabing eh whats it take to get a coffe over here

  glm::dvec3 a(incomingRay.from);
  glm::dvec3 d(incomingRay.v);

  // The coefficients as described in the comment above
  float A = glm::dot(d, d);
  float B = 2 * glm::dot(d, a);
  float C = glm::dot(a, a) - 1;

  double roots[2];
  size_t numRoots = quadraticRoots(A, B, C, roots);

  if (numRoots == 0) {
    // Total miss
    return new Intersection(GeometryIntersection::Miss);
  }

  // For ray a + td, the closest t for which we intersect the sphere
  double t;

  if (numRoots == 1) {
    // Easy case
    float root = roots[0];
    
    // But still reject if its behind us
    if (root < 0) {
      return new Intersection(GeometryIntersection::Past);
    }

    t = roots[0];
  }

  // Great we intersect twice, but the sphere could still be behind us
  GeometryIntersection::ShooterPos shooterPos;
  if (numRoots == 2) {
    float l, r;
    l = roots[0];
    r = roots[1];
    Log::trace(METHOD_NAME, "l {} r {}", l , r);
    if (l < 0 && r < 0) {
      // The whole sphere is behind us
      return new Intersection(GeometryIntersection::Past);
    } else if (l < 0 || r < 0) {
      // One of the intersections in certainly behind us
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

  Log::trace(METHOD_NAME, "t {}", t);
  Point pointOfIntersection = incomingRay.pointAt(t);

  // Since we already assume the sphere is centered at 0,0,0, the normal
  // is the same as the point of intersection
  Vector normal = Vector(pointOfIntersection);

  return new GeometryIntersection(shooterPos, 
      pointOfIntersection, normal);
}
