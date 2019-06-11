#pragma once

#include "Object.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>

// Forward declare
class Mesh;

class MeshLoader : public Object {
  const std::string &filename;

public:
  MeshLoader(const std::string &filename);
  virtual ~MeshLoader();

  virtual void loadMesh(Mesh *mesh) const;

  virtual const char * type() const {
    return "MeshLoader";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << filename;
  }

private:
  static bool verifyScene(const aiScene *scene);

};
