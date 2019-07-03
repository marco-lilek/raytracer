#include "MeshLoader.hpp"
#include "Mesh.hpp"
#include "UVMesh.hpp"
#include "Log.hpp"

using namespace std;
using namespace Glm;

MeshLoader::MeshLoader(const std::string &filename) : filename(filename) {
}

MeshLoader::~MeshLoader() {}

bool
MeshLoader::verifyScene(
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

const aiScene *MeshLoader::loadScene(
    Assimp::Importer &importer) const {
  const char *TRACE_HEADER = "MeshLoader::loadScene";

  // TODO dont hardcode
  string fullpath = "../assets/obj/" + filename;

  Log::debug(TRACE_HEADER, "loading model from {}", fullpath);
  const aiScene *scene = importer.ReadFile(fullpath,0);

  CHECK(TRACE_HEADER, verifyScene(scene));
  return scene;
}

void MeshLoader::loadMesh(Mesh *mesh) const {
  const char *TRACE_HEADER = "MeshLoader::loadMesh";
  Assimp::Importer importer;
  const aiScene *scene = loadScene(importer);
  const aiMesh *aiMesh = scene->mMeshes[0];
  // TODO assert there is exactly 1 mesh in the scene
  loadPositions(aiMesh, mesh);
  Log::info(TRACE_HEADER, "loaded mesh from {}", filename);
}

void MeshLoader::loadMesh(UVMesh *mesh) const {
  const char *TRACE_HEADER = "MeshLoader::loadMesh";

  Assimp::Importer importer;
  const aiScene *scene = loadScene(importer);
  const aiMesh *aiMesh = scene->mMeshes[0];
  int nv = aiMesh->mNumVertices;
  // TODO assert there is exactly 1 mesh in the scene
  loadPositions(aiMesh, mesh);

  mesh->normals.resize(nv);
  mesh->uvCoords.resize(nv);

  for (int i = 0; i < nv; i++) {
    auto normal = aiMesh->mNormals[i];
    auto uvcoord = aiMesh->mTextureCoords[0][i];

    mesh->normals[i] = Vec3(normal.x, normal.y, normal.z);
    mesh->uvCoords[i] = Vec2((double)uvcoord.x, (double)uvcoord.y);
  }

  mesh->tangents.resize(nv);

  scene = importer.ApplyPostProcessing(
    aiProcess_CalcTangentSpace);
  CHECK(TRACE_HEADER, verifyScene(scene));

  for (int i = 0; i < nv; i++) {
    auto tangent = aiMesh->mTangents[i];
    mesh->tangents[i] = Vec3(
        tangent.x, tangent.y, tangent.z);
  }

  Log::info(TRACE_HEADER, "loaded uvmesh from {}", filename);
}

const int MeshLoader::loadPositions(
    const aiMesh* aiMesh, Mesh *mesh) const {
  const char *TRACE_HEADER = "MeshLoader::loadVertices";
  int numVertices = aiMesh->mNumVertices;
  Log::debug(TRACE_HEADER, "numVertices {}", numVertices);

  mesh->positions.resize(numVertices);
  for (int i = 0; i < numVertices; i++) {
    auto vertex = aiMesh->mVertices[i];
    mesh->positions[i] = glm::dvec3(vertex.x, vertex.y, vertex.z);
  }
  return numVertices;
}

