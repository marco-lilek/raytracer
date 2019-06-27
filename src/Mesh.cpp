#include "Mesh.hpp"
#include "ObjLoader.hpp"
#include "Log.hpp"
#include "Constants.hpp"
#include "MeshLoader.hpp"

#include "GeometryIntersection.hpp"

#include <iostream>

using namespace std;

Mesh::Mesh(const std::string &name) : Geometry()
{
  MeshLoader loader(name);
  loader.loadMesh(this);
}

Intersection *Mesh::intersect(const Ray &incomingRay) const {
  int hitFace = -1;
  double closestDistToIntersect = -1;
  double beta = -1;
  double gamma = -1;

  const glm::dvec3 &ev = incomingRay.from;
  const glm::dvec3 dv(incomingRay.v);
  double a, b, c, d, e, f, g, h, i, j, k, l;
  for (int faceIdx = 0; faceIdx < positions.size(); faceIdx += 3) {
    glm::dvec3 va(positions[faceIdx]);
    glm::dvec3 vb(positions[faceIdx + 1]);
    glm::dvec3 vc(positions[faceIdx + 2]);

    // TODO explain how this works
    a = va.x - vb.x; b = va.y - vb.y; c = va.z - vb.z;
    d = va.x - vc.x; e = va.y - vc.y; f = va.z - vc.z;

    g = dv.x; h = dv.y; i = dv.z;
    j = va.x - ev.x; k = va.y - ev.y; l = va.z - ev.z;

    double M = a * (e * i - h * f) + b * (g * f - d * i) +
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

    if (thisBeta + thisGamma >= 1.0) {
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

  glm::vec3 va(positions[hitFace]);
  glm::vec3 vb(positions[hitFace + 1]);
  glm::vec3 vc(positions[hitFace + 2]);

  Vector normal(glm::cross(vb - va, vc - vb));
  Point poi(incomingRay.pointAt(closestDistToIntersect));

  return new GeometryIntersection(
      GeometryIntersection::Towards,
      poi, normal);
}
