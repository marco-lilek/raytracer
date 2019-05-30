#include "Cube.hpp"

#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <polyroots.hpp>

using namespace std;

GeometryIntersection Cube::intersect(const Ray &incomingRay) const {
    return GeometryIntersection(GeometryIntersection::Miss);
}

// bool
// Cube::intersect(
//   const Ray &r, float &t, glm::dvec4 &normal) const
// {
  // glm::dvec3 e(r.from);
  // glm::dvec3 d(r.v);

  // // x,y,z = 0,1,2
  // static const int planes[3][2] = {{1, 2}, {0, 2}, {0, 1}};

  // bool intersect = false;

  // float offst = -0.5;
  // for (int corner = 0; corner < 2; corner++) { // 0 or 1
  //   for (int planePair = 0; planePair < 3;
  //        planePair++) { // 0,1,2
  //     glm::dvec3 n(0);
  //     n[planePair] = 2 * corner - 1; // 0,1 -> -1,1
  //     glm::dvec3 p1(corner + offst); // Point on the plane

  //     double dDotn = glm::dot(d, n);
  //     if (dDotn == 0)
  //       continue; // Perpendicular

  //     double lt = glm::dot(p1 - e, n) / dDotn;
  //     if (lt < 0)
  //       continue; // No intersection
  //     if (intersect && lt > t)
  //       continue; // Ray already intersected the cube at a
  //                 // closer point

  //     glm::dvec3 thisP(Ray::pointAt(r, lt));

  //     double pp0 = thisP[planes[planePair][0]];
  //     double pp1 = thisP[planes[planePair][1]];
  //     if (pp0 < 0 + offst || pp0 > 1 + offst)
  //       continue;
  //     if (pp1 < 0 + offst || pp1 > 1 + offst)
  //       continue;

  //     intersect = true;
  //     t = lt;
  //     normal = glm::dvec4(n, 0);
  //   }
  // }

  // return intersect;
  // return false;
// }
