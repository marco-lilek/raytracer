#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

void importModel(
  const std::string &fname,
  std::vector<glm::vec3> &positions,
  std::vector<glm::vec3> &normals,
  std::vector<glm::vec2> &uvCoords,
  std::vector<glm::vec3> &tangents);
