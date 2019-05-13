#include "UVMesh.hpp"

void
UVMesh::importElements(
  Assimp::Importer &importer,
  const aiScene *scene)
{
  Mesh::importElements(importer, scene);

  aiMesh *mesh = scene->mMeshes[0];
  const int nv = mesh->mNumVertices;

  normals.resize(nv);
  uvCoords.resize(nv);

  for (int i = 0; i < nv; i++) {
    auto normal = mesh->mNormals[i];
    auto uvcoord = mesh->mTextureCoords[0][i];

    normals[i] = glm::vec3(normal.x, normal.y, normal.z);
    uvCoords[i] = glm::vec2(uvcoord.x, uvcoord.y);
  }

  tangents.resize(nv);

  scene = importer.ApplyPostProcessing(
    aiProcess_CalcTangentSpace);
  assert(verifyScene(scene));

  for (int i = 0; i < nv; i++) {
    auto tangent = mesh->mTangents[i];
    tangents[i] =
      glm::vec3(tangent.x, tangent.y, tangent.z);
  }
}

bool
UVMesh::intersect(
  const Ray &r, float &t, glm::dvec4 &normal) const
{
  int hitFace;
  double beta;
  double gamma;
  bool intersects = _intersect(r, t, hitFace, beta, gamma);
  if (intersects) {
    glm::vec3 va(positions[hitFace]);
    glm::vec3 vb(positions[hitFace + 1]);
    glm::vec3 vc(positions[hitFace + 2]);

    // TODO: interpolate the normals
    normal = glm::vec4(glm::cross(vb - va, vc - vb), 0);
  }

  return intersects;
}
