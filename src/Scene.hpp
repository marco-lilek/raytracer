//
// Created by mllilek on 10/19/19.
//

#pragma once

#include <stack>
#include <list>
#include "Node.hpp"
#include "Light.hpp"
#include "PhongMaterial.hpp"
#include "MirrorMaterial.hpp"

class Scene {
  const Node *root;
  std::vector<const Light *> lights;
  glm::dvec3 globalIllumination;

public:
  glm::dvec3 getColor(const Ray &r);

  Scene(const Node *const root,
        const std::vector<const Light *> lights,
        const glm::dvec3 &ambient);

private:
  glm::dvec3 getColor(
          const Ray &r,
          int depth) const;

  glm::dvec3
  getColorOfRayOnPhongMaterial(
          const PhongMaterial *material,
          const Ray &rayFromEye,
          const Intersection &intersection) const;

  glm::dvec3
  getColorOfRayOnMirror(const MirrorMaterial *material,
          const Ray &rayFromEye,
          const Intersection &intersection,
          const int depth) const;
};

