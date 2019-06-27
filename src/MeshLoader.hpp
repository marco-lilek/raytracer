#pragma once

#include "Object.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>

class Mesh;
class UVMesh;

class MeshLoader : public Object {
  const std::string &filename;

public:
  MeshLoader(const std::string &filename);
  virtual ~MeshLoader();

  void loadMesh(Mesh *mesh) const;
  void loadMesh(UVMesh *mesh) const;

  virtual const char * type() const {
    return "MeshLoader";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << filename;
  }

private:
  static bool verifyScene(const aiScene *scene);

  const aiScene *loadScene(Assimp::Importer &importer) const;
  const int loadPositions(const aiMesh* aiMesh, Mesh *mesh) const;
};
