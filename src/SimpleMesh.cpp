#include "SimpleMesh.hpp"
#include "Log.hpp"
#include "Constants.hpp"

#include "GeometryIntersection.hpp"

#include <iostream>

#include "Glm.hpp"

using namespace Glm;
using namespace std;

SimpleMesh::SimpleMesh(const std::string &name) : Mesh(name)
{
  const char *TRACE_HEADER = "SimpleMesh::SimpleMesh";
  Assimp::Importer importer;
  const aiScene *scene = loadScene(importer);
  const aiMesh *aiMesh = scene->mMeshes[0];
  // TODO assert there is exactly 1 mesh in the scene
  loadPositions(aiMesh);
  Log::info(TRACE_HEADER, "loaded mesh from {}", name);
}

Intersection *SimpleMesh::constructIntersection(
      int hitFace, Vec4 poi, double beta, double gamma) const {

  Vec3 va(positions[hitFace]);
  Vec3 vb(positions[hitFace + 1]);
  Vec3 vc(positions[hitFace + 2]);

  Vec4 normal(glm::cross(vb - va, vc - vb), 0);

  return new GeometryIntersection(
      GeometryIntersection::Towards,
      poi, 
      normal);
}
