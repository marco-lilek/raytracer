#pragma once

#include <glm/glm.hpp>

class Point {
const glm::dvec4 p;

public:
  Point(double x, double y, double z) : p(x,y,z,0) {}
};
