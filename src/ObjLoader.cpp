#include "Log.hpp"
#include "ObjLoader.hpp"

using namespace std;
using namespace glm;

void importModel(
                 const string &fname,
                 std::vector<vec3> &positions,
                 std::vector<vec3> &normals,
                 std::vector<vec2> &uvCoords,
                 std::vector<vec3> &tangents
                 )
{
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(fname,
                                           aiProcess_FlipUVs |
                                           aiProcess_GenSmoothNormals |
                                           aiProcess_FixInfacingNormals |
                                           aiProcess_FindInvalidData);
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    Log::error("Assimp import of model {} failed", fname);
    assert(0);
  }

  Log::debug("Loading model {}", fname);
  aiMesh *mesh = scene->mMeshes[0];
  const int nv = mesh->mNumVertices;
  Log::debug("Found {} vertices", nv);

  positions.resize(nv);
  uvCoords.resize(nv);
  tangents.resize(nv);
  normals.resize(nv);

  for (int i = 0; i < nv; i++) {
    auto vertex = mesh->mVertices[i];
    auto uvcoord = mesh->mTextureCoords[0][i];
    auto normal = mesh->mNormals[i];

    positions[i] = glm::vec3(vertex.x, vertex.y, vertex.z);
    uvCoords[i] = glm::vec2(uvcoord.x, uvcoord.y);
    normals[i] = glm::vec3(normal.x, normal.y, normal.z);
  }

  // Needs to be done after all other post processing
  scene = importer.ApplyPostProcessing(aiProcess_CalcTangentSpace);

  for (int i = 0; i < nv;i++) {
    auto tangent = mesh->mTangents[i];
    tangents[i] = glm::vec3(tangent.x, tangent.y, tangent.z);
    //assert(glm::dot(tangents[i], normals[i]) == 0);
  }
}
