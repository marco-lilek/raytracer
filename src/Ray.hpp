//
// Created by mllilek on 10/15/19.
//
#pragma once

#include <glm/detail/type_vec.hpp>
#include <glm/vec4.hpp>

struct Ray {
  glm::dvec4 p;
  glm::dvec4 v;
  Ray(const glm::dvec4 &p,const glm::dvec4 &v) : p(p), v(v) {}
};


