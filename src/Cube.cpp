#include "Cube.hpp"
#include "Log.hpp"

#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <polyroots.hpp>

#include "GeometryIntersection.hpp"

using namespace std;

Intersection *Cube::intersect(const Ray &incomingRay) const {
  const char *METHOD_NAME = "Cube::intersect";
  // TODO for now just incorrectly report all non-Towards intersections
  // as misses, eventually get Inside properly detected too
  
  // Incoming ray is e + td, for some t
  glm::dvec3 e(incomingRay.from);
  glm::dvec3 d(incomingRay.v);

  Log::trace(METHOD_NAME, "e {} d {}", to_string(e), to_string(d));

  // We'll test for intersections with every plane twice for a total of 6 checks
  // x,y,z = 0,1,2
  // y,z   x,z   x,y
  static const int planeAxes[3][2] = {{1, 2}, {0, 2}, {0, 1}};

  bool intersectWithCube = false;

  // We need to find the smallest positive t for which we intersect the cube
  double t;
  Point closestPoi;
  Vector normalAtIntersection;
  for (int planeIdx = 0; planeIdx <= 2; planeIdx++) { // 0,1,2
    for (int corner = 0; corner <= 1; corner++) { // 0,0,0 or 1,1,1
      Log::trace(METHOD_NAME, "planeIdx {} corner {}",
          planeIdx, corner);
      glm::dvec3 normal(0);

      // 0,1 -> -1,1
      // the normal of the xz plane cornered at 0,0,0 is -y etc
      normal[planeIdx] = 2 * corner - 1;

      glm::dvec3 p1(corner); // Point on the plane

      // Project our incoming ray onto the plane
      double dDotn = glm::dot(d, normal);
      if (dDotn == 0) {
        // Perpendicular, not intersecting
        continue; 
      }

      // A ray always intersects with a plane unless they are perpendicular
      //
      // P is a point on the incomingRay if P = e + td for some t
      // Q is a point on the plane if dot(p - Q,n) = 0 
      // (for some other point on the plane p)
      // then, for the ray to intersect the plane there must be some t for which
      // dot(p - (e + td), n) = 0
      // expand then rearrage to solve for t
      // t = dot(p - e, n) / dot(d, n) 
      double lt = glm::dot(p1 - e, normal) / dDotn;
      if (lt < 0) {
        continue; // No intersection
      }
      Log::trace(METHOD_NAME, "lt {}", lt);
      if (intersectWithCube && t < lt) {
        // Ray already intersected the cube at a closer point
        continue;
      }

      // point of intersection
      glm::dvec3 poi(e + lt * d);
      Log::trace(METHOD_NAME, "poi {}", to_string(poi));

      // Since the cube is axis aligned we can easily get where the point of
      // intersection falls along each of the axes of the plane
      bool intersectsPlane = true;
      for (int axis = 0; axis <= 1; axis++) {
        double poiAlongAxis = poi[planeAxes[planeIdx][axis]];
        // If we fall outside of a 1x1 square then fuggetaboutit
        if (poiAlongAxis < 0 || poiAlongAxis > 1) {
          intersectsPlane = false;
        }
      }
      if (!intersectsPlane) {
        continue;
      }

      // We reached this far, this means that this was our closest
      // point of intersection YET
      intersectWithCube = true;
      t = lt;
      closestPoi = poi;
      normalAtIntersection = Vector(normal);
    }
  }

  if (!intersectWithCube) {
    return new Intersection(GeometryIntersection::Miss);
  }

  Log::trace(METHOD_NAME, "closestPoi {}" , closestPoi);

  return new GeometryIntersection(
      GeometryIntersection::Towards,
      closestPoi,
      normalAtIntersection);
}
