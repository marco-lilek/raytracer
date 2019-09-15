#include "UVMesh.hpp"
#include "UVIntersection.hpp"
#include "Log.hpp"
#include "Constants.hpp"

using namespace Glm;

UVMesh::UVMesh(const std::string &name) : Mesh(name)
{
  const char *TRACE_HEADER = "UVMesh::UVMesh";

  Assimp::Importer importer;
  const aiScene *scene = loadScene(importer);
  const aiMesh *aiMesh = scene->mMeshes[0];
  int nv = aiMesh->mNumVertices;
  // TODO assert there is exactly 1 mesh in the scene
  loadPositions(aiMesh);

  normals.resize(nv);
  uvCoords.resize(nv);

  for (int i = 0; i < nv; i++) {
    auto normal = aiMesh->mNormals[i];
    auto uvcoord = aiMesh->mTextureCoords[0][i];

    normals[i] = Vec3(normal.x, normal.y, normal.z);
    uvCoords[i] = Vec2((double)uvcoord.x, (double)uvcoord.y);
  }

  tangents.resize(nv);

  // TODO maybe generate smooth normals
  scene = importer.ApplyPostProcessing(
    aiProcess_CalcTangentSpace);
  CHECK(TRACE_HEADER, verifyScene(scene));

  for (int i = 0; i < nv; i++) {
    auto tangent = aiMesh->mTangents[i];
    tangents[i] = Vec3(
        tangent.x, tangent.y, tangent.z);
  }

  Log::info(TRACE_HEADER, "loaded uvmesh from {}", name);
}

Intersection *UVMesh::constructIntersection(
      int hitFace,
      Vec4 poi,
      double beta,
      double gamma) const {
  const char *METHOD_NAME = "UVMesh::constructIntersection";

  double ua(uvCoords[hitFace][0]);
  double ub(uvCoords[hitFace+1][0]);
  double uc(uvCoords[hitFace+2][0]);

  double va(uvCoords[hitFace][1]);
  double vb(uvCoords[hitFace+1][1]);
  double vc(uvCoords[hitFace+2][1]);

  double alpha = (1.0 - beta - gamma);
  Log::check(METHOD_NAME, alpha + constants::EPSILON >= 0, "alpha {}", alpha);
  double u = glm::clamp(alpha * ua + beta * ub + gamma * uc, 0.0, 1.0);
  double v = glm::clamp(alpha * va + beta * vb + gamma * vc, 0.0, 1.0);

  Vec3 na(normals[hitFace]);
  Vec3 nb(normals[hitFace + 1]);
  Vec3 nc(normals[hitFace + 2]);

  // This time we have the normal available in the mesh info
  Vec4 normal(alpha  * na + beta * nb + gamma * nc, 0);

  Vec3 ta(tangents[hitFace]);
  Vec3 tb(tangents[hitFace + 1]);
  Vec3 tc(tangents[hitFace + 2]);

  Vec4 tangent(alpha  * ta + beta * tb + gamma * tc, 0);

  return new UVIntersection(
      GeometryIntersection::Towards,
      poi, 
      normal, 
      tangent,
      u,
      v);
}

// void
// UVMesh::importElements(
//   Assimp::Importer &importer,
//   const aiScene *scene)
// {
//   Mesh::importElements(importer, scene);

//   aiMesh *mesh = scene->mMeshes[0];
//   const int nv = mesh->mNumVertices;

//   normals.resize(nv);
//   uvCoords.resize(nv);

//   for (int i = 0; i < nv; i++) {
//     auto normal = mesh->mNormals[i];
//     auto uvcoord = mesh->mTextureCoords[0][i];

//     normals[i] = glm::vec3(normal.x, normal.y, normal.z);
//     uvCoords[i] = glm::vec2(uvcoord.x, uvcoord.y);
//   }

//   tangents.resize(nv);

//   scene = importer.ApplyPostProcessing(
//     aiProcess_CalcTangentSpace);
//   assert(verifyScene(scene));

//   for (int i = 0; i < nv; i++) {
//     auto tangent = mesh->mTangents[i];
//     tangents[i] =
//       glm::vec3(tangent.x, tangent.y, tangent.z);
//   }
// }

// bool
// UVMesh::intersect(
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

//     // TODO: interpolate the normals
//     normal = glm::vec4(glm::cross(vb - va, vc - vb), 0);
//   }

//   return intersects;
// }
