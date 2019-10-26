//
// Created by mllilek on 10/16/19.
//

#pragma once

#include <glm/detail/type_vec.hpp>
#include <glm/vec4.hpp>

struct GeometryNode;

struct Intersection {
  enum Type {
    CompleteMiss,
    ObjectBehindRay,
    RayInsideObject,
    RayHitsObject
  };

  bool isHit() const {
    return type == RayInsideObject || type == RayHitsObject;
  }

  Type type;
  const GeometryNode *node;
  glm::dvec4 p;
  glm::dvec4 n;

  // UV
  double u,v;
  glm::dvec4 t;

  Intersection &operator=( const Intersection& o) = default;
  Intersection() {
    type = Type::CompleteMiss;
    node = (GeometryNode*)0xdeadbeef;
    p = glm::dvec4(0);
    n = glm::dvec4(0);
    u = 0;
    v = 0;
    t = glm::dvec4(0);
  }
};

