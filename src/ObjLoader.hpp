#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

void importModel(
  const std::string &fname,
  std::vector<glm::dvec3> &positions);
  // std::vector<glm::dvec3> &normals,
  // std::vector<glm::dvec2> &uvCoords,
  // std::vector<glm::dvec3> &tangents);

void importModel(
  const std::string &fname,
  std::vector<glm::dvec3> &positions,
  std::vector<glm::dvec3> &normals,
  std::vector<glm::dvec2> &uvCoords,
  std::vector<glm::dvec3> &tangents);
