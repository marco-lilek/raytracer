#pragma once

#include <glm/gtx/string_cast.hpp>

std::ostream& operator<<(std::ostream& out, const glm::dvec3& g);
std::ostream& operator<<(std::ostream& out, const glm::dvec4& g);
std::ostream& operator<<(std::ostream& out, const glm::dmat4& g);
std::ostream& operator<<(std::ostream& out, const glm::dmat3& g);

