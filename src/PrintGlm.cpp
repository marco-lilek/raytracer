//
// Created by mllilek on 10/15/19.
//
#include "PrintGlm.hpp"

std::ostream& operator<<(std::ostream& out, const glm::dvec3& g) {
  return out << to_string(g);
}

std::ostream& operator<<(std::ostream& out, const glm::dvec4& g) {
  return out << to_string(g);
}

std::ostream& operator<<(std::ostream& out, const glm::dmat4& g) {
  return out << to_string(g);
}

std::ostream& operator<<(std::ostream& out, const glm::dmat3& g) {
  return out << to_string(g);
}

