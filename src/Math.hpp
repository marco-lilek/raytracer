#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace math {
double
normalizedDot(const glm::dvec4 &a, const glm::dvec4 &b);
glm::dvec4
halfwayVector(const glm::dvec4 &a, const glm::dvec4 &b);
} // namespace math
