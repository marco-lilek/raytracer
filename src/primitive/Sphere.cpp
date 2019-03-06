#include "primitive/Sphere.hpp"
#include <iostream>
#include <polyroots.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;

bool Sphere::intersect(const Ray &r, float &t, glm::dvec4 &normal) const {
  // NOTE: Making the assumption that c = 0
  glm::dvec3 a(r.from);
  glm::dvec3 d(r.v);

  //cerr << "a " << glm::to_string(a) << " d " << glm::to_string(d) << endl;

  float A = glm::dot(d, d);
  float B = 2 * glm::dot(d, a);
  float C = glm::dot(a, a) - 1; // Just assume the radius is 1

  double roots[2];
  size_t numRoots = quadraticRoots(A, B, C, roots);
  //cerr << "numroots " << numRoots << endl;

  if (numRoots == 0) return false;
  if (numRoots == 1) t = roots[0];
  if (numRoots == 2) {
    float l, r;
    l = roots[0];
    r = roots[1];
    //cerr << "l " << l << " r " << r << endl;
    if (l < 0 && r < 0) return false; // No roots?
    if (l < 0 || r < 0) {
      t = glm::max(l,r); // The non-neg one
    } else {
      t = glm::min(l, r); // Intersection thats closer to the origin
    }
  }

  //cerr << "t " << t << endl;
  glm::dvec4 P = Ray::pointAt(r, t);
  float dist = glm::distance(P, glm::dvec4(0,0,0,1));

  // Don't need to normalize it (and we shouldn't to avoid acc error),
  // just do the normalization when its actually used
  normal = glm::dvec4(glm::dvec3(P) - glm::dvec3(0),0); // from center to point on the sphere
  //cerr << "dist" << glm::distance(P, glm::dvec4(0,0,0,1)) << endl;
  return true;

}
