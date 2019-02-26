#include "Primitive.hpp"
#include "polyroots.hpp"

bool Sphere::intersect(const Ray &r, float &t, glm::vec4 &normal) const {
  // NOTE: Making the assumption that c = 0
  glm::dvec3 a(r.from);
  glm::dvec3 d(r.v);
  float A = glm::dot(d, d);
  float B = 2 * glm::dot(d, a);
  float C = glm::dot(a, a) - radius * radius;

  double roots[2];
  size_t numRoots = quadraticRoots(A, B, C, roots);

  if (numRoots == 0) return false;
  if (numRoots == 1) t = roots[0];
  if (numRoots == 2) {
    float l, r;
    l = roots[0];
    r = roots[1];
    if (l < 0 && r < 0) return false; // No roots?
    if (l < 0 || r < 0) {
      t = glm::max(l,r); // The non-neg one
    } else {
      t = glm::min(l, r); // Intersection thats closer to the origin
    }
  }

  glm::vec4 P = r.pointAt(t);
  float dist = glm::distance(P, glm::vec4(0,0,0,1));

  // Don't need to normalize it (and we shouldn't to avoid acc error),
  // just do the normalization when its actually used
  normal = glm::vec4(glm::vec3(P) - glm::vec3(0),0); // from center to point on the sphere
  return true;

}