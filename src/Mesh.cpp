#include "Mesh.hpp"
#include "ObjLoader.hpp"
#include "Log.hpp"
#include "Constants.hpp"

#include <iostream>

using namespace std;

bool
Mesh::verifyScene(
  const aiScene *scene)
{
  if (!scene)
    return false;
  if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
    return false;
  if (!scene->mRootNode)
    return false;

  return true;
}

void
Mesh::importElements(
  Assimp::Importer &importer,
  const aiScene *scene)
{
  const aiMesh *mesh = scene->mMeshes[0];
  int nv = mesh->mNumVertices;
  positions.resize(nv);
  for (int i = 0; i < nv; i++) {
    auto vertex = mesh->mVertices[i];
    positions[i] = glm::vec3(vertex.x, vertex.y, vertex.z);
  }
}

Mesh::Mesh(const std::string &name) : Primitive()
{
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(
    "../src/models/" + name,0);
  importElements(importer, scene);
}

// bool
// Mesh::_intersect(
//   const Ray &r, float &t, int &hitFace, double &beta, double &gamma) const
// {
//   return false;
  // bool foundIntersection = false;

  // glm::vec3 ev(r.from);
  // glm::vec3 dv(r.v);
  // double a, b, c, d, e, f, g, h, i, j, k, l;
  // for (int fidx = 0; fidx < positions.size(); fidx += 3) {
  //   glm::vec3 va(positions[fidx]);
  //   glm::vec3 vb(positions[fidx + 1]);
  //   glm::vec3 vc(positions[fidx + 2]);

  //   a = va.x - vb.x;
  //   b = va.y - vb.y;
  //   c = va.z - vb.z;
  //   d = va.x - vc.x;
  //   e = va.y - vc.y;
  //   f = va.z - vc.z;
  //   g = dv.x;
  //   h = dv.y;
  //   i = dv.z;

  //   j = va.x - ev.x;
  //   k = va.y - ev.y;
  //   l = va.z - ev.z;

  //   double M = a * (e * i - h * f) + b * (g * f - d * i) +
  //              c * (d * h - e * g);

  //   double tp =
  //     -(f * (a * k - j * b) + e * (j * c - a * l) +
  //       d * (b * l - k * c)) / M;

  //   if (tp < constants::EPSILON)
  //     continue; // Doesnt intersect this plane
  //   if (foundIntersection && tp > t)
  //     continue; // We've already intersected at a nearer
  //               // point

  //   double thisGamma =
  //     (i * (a * k - j * b) + h * (j * c - a * l) +
  //      g * (b * l - k * c)) /
  //     M;

  //   if (thisGamma < 0 || thisGamma > 1)
  //     continue;

  //   double thisBeta =
  //     (j * (e * i - h * f) + k * (g * f - d * i) +
  //      l * (d * h - e * g)) / M;

  //   if (thisBeta < 0) continue;

  //   if (thisBeta + thisGamma != 1.0 &&
  //       thisBeta + thisGamma > 1)
  //       continue;

  //   t = tp;
  //   hitFace = fidx;
  //   beta = thisBeta;
  //   gamma = thisGamma;

  //   foundIntersection = true;
  // }

  // return foundIntersection;
// }

// bool
// Mesh::intersect(
//   const Ray &r, float &t, glm::dvec4 &normal) const
// {
//   int hitFace;
//   double beta;
//   double gamma;
//   bool intersects = _intersect(r, t, hitFace, beta, gamma);
//   if (intersects) {
//     glm::vec3 va(positions[hitFace]);
//     glm::vec3 vb(positions[hitFace + 1]);
//     glm::vec3 vc(positions[hitFace + 2]);

//     normal = glm::vec4(glm::cross(vb - va, vc - vb), 0);
//   }

//   return intersects;
// }
