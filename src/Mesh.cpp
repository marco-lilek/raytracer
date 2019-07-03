#include "Mesh.hpp"
#include "Log.hpp"
#include "Constants.hpp"
#include "MeshLoader.hpp"

#include "GeometryIntersection.hpp"

#include <iostream>

#include "Glm.hpp"

using namespace Glm;
using namespace std;

Mesh::Mesh(const std::string &name) : Geometry()
{
}

Intersection *Mesh::intersect(const Ray &incomingRay) const {
  int hitFace = -1;
  double closestDistToIntersect = -1;
  double beta = -1;
  double gamma = -1;

  const Vec3 &ev = incomingRay.from;
  const Vec3 dv(incomingRay.v);
  double a, b, c, d, e, f, g, h, i, j, k, l;
  for (int faceIdx = 0; faceIdx < positions.size(); faceIdx += 3) {
    Vec3 va(positions[faceIdx]);
    Vec3 vb(positions[faceIdx + 1]);
    Vec3 vc(positions[faceIdx + 2]);

    // TODO explain how this works
    a = va.x - vb.x; b = va.y - vb.y; c = va.z - vb.z;
    d = va.x - vc.x; e = va.y - vc.y; f = va.z - vc.z;

    g = dv.x; h = dv.y; i = dv.z;
    j = va.x - ev.x; k = va.y - ev.y; l = va.z - ev.z;

    double M = a * (e * i - h * f) + 
               b * (g * f - d * i) +
               c * (d * h - e * g);

    double distToIntersect = -(
        f * (a * k - j * b) + 
        e * (j * c - a * l) + 
        d * (b * l - k * c)) / M;

    if (distToIntersect < 0.0) {
      // Doesnt intersect this plane
      continue; 
    }


    if (hitFace != -1 && distToIntersect > closestDistToIntersect) {
      // We've already intersected at a nearer
      // point                                      
      continue;
    }
                
    double thisGamma =
      (i * (a * k - j * b) + 
       h * (j * c - a * l) +
       g * (b * l - k * c)) / M;
    

    if (thisGamma < 0.0 || thisGamma > 1.0) {
      continue;
    }

    double thisBeta =
      (j * (e * i - h * f) + k * (g * f - d * i) +
       l * (d * h - e * g)) / M;

    if (thisBeta < 0.0) {
      continue;
    } 

    if (thisBeta + thisGamma - constants::EPSILON > 1.0) {
        continue;
    }

    closestDistToIntersect = distToIntersect;
    hitFace = faceIdx;
    beta = thisBeta;
    gamma = thisGamma;
  }

  // TODO not all misses are full misses
  if (hitFace == -1) {
    return new Intersection(GeometryIntersection::Miss);
  }

  Vec4 poi(incomingRay.pointAt(closestDistToIntersect));
  return constructIntersection(hitFace, poi, beta, gamma);
}

Intersection *Mesh::constructIntersection(
      int hitFace, Vec4 poi, double beta, double gamma) const {

  Vec3 va(positions[hitFace]);
  Vec3 vb(positions[hitFace + 1]);
  Vec3 vc(positions[hitFace + 2]);

  Vec4 normal(glm::cross(vb - va, vc - vb), 0);

  return new GeometryIntersection(
      GeometryIntersection::Towards,
      poi, 
      normal);
}
