#pragma once

#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

void importModel(
                 const std::string &fname,
                 std::vector<glm::vec3> &positions,
                 std::vector<glm::vec3> &normals,
                 std::vector<glm::vec2> &uvCoords,
                 std::vector<glm::vec3> &tangents
                 );
