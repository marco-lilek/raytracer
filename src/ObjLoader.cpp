#include "ObjLoader.hpp"
#include "Log.hpp"

using namespace std;
using namespace glm;

namespace {

bool
verifyScene(const aiScene *scene)
{
  scene->mAnimations;
  if (!scene)
    return false;
  if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
    return false;
  if (!scene->mRootNode)
    return false;

  return true;
}

} // namespace

void
importModel(
  const string &fname, std::vector<dvec3> &positions)
{
  const char *LOCATION = "importModel";
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(fname, 0);
  assert(verifyScene(scene));

  Log::debug(LOCATION, "Loading model {}", fname);
  aiMesh *mesh = scene->mMeshes[0];
  const int nv = mesh->mNumVertices;
  Log::debug(LOCATION, "Found {} vertices", nv);

  positions.resize(nv);

  for (int i = 0; i < nv; i++) {
    auto vertex = mesh->mVertices[i];
    positions[i] = glm::vec3(vertex.x, vertex.y, vertex.z);
  }
}

void
importModel(
  const string &fname,
  std::vector<dvec3> &positions,
  std::vector<dvec3> &normals,
  std::vector<dvec3> &tangents,
  std::vector<dvec2> &uvCoords)
{
  const char *LOCATION = "importModel";
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(fname, 0);
  assert(verifyScene(scene));

  Log::debug(LOCATION, "Loading model {}", fname);
  aiMesh *mesh = scene->mMeshes[0];
  const int nv = mesh->mNumVertices;
  Log::debug(LOCATION, "Found {} vertices", nv);

  positions.resize(nv);
  normals.resize(nv);
  tangents.resize(nv);
  uvCoords.resize(nv);

  for (int i = 0; i < nv; i++) {
    auto vertex = mesh->mVertices[i];
    auto normal = mesh->mNormals[i];
    auto uvcoord = mesh->mTextureCoords[0][i];

    positions[i] = glm::vec3(vertex.x, vertex.y, vertex.z);
    normals[i] = glm::vec3(normal.x, normal.y, normal.z);
    uvCoords[i] = glm::vec2(uvcoord.x, uvcoord.y);
  }

  // Needs to be done after all other post processing
  scene = importer.ApplyPostProcessing(
    aiProcess_CalcTangentSpace);
  assert(verifyScene(scene));

  for (int i = 0; i < nv; i++) {
    auto tangent = mesh->mTangents[i];
    tangents[i] =
      glm::vec3(tangent.x, tangent.y, tangent.z);
  }
}
