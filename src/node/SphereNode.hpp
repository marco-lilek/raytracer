#pragma once

#include "node/GeometryNode.hpp"
#include "primitive/Sphere.hpp"

struct SphereNode : GeometryNode {
  Sphere s;

  SphereNode(const std::string &name, 
             const Material *m) : 
    GeometryNode(name, &s, m)
  {}
};
