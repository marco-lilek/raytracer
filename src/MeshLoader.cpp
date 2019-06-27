#include "MeshLoader.hpp"
#include "Mesh.hpp"
#include "Log.hpp"

using namespace std;

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

  int numVertices = aiMesh->mNumVertices;
  Log::debug(TRACE_HEADER, "numVertices {}", numVertices);

  mesh->positions.resize(numVertices);
  for (int i = 0; i < numVertices; i++) {
    auto vertex = aiMesh->mVertices[i];
    mesh->positions[i] = glm::dvec3(vertex.x, vertex.y, vertex.z);
  }
}

