#pragma once

#include "Color.hpp"
#include "Light.hpp"
#include "LightRay.hpp"
#include "GeometryIntersection.hpp"
#include <vector>

class Node;
class PhongMaterial;

struct Scene {
  const Node *const root;
  const std::vector<const Light *> lights;
  glm::dvec3 ambientLight;

  // const glm::dvec3 fireRay(const LightRay &r) const;

public:
  Scene(
    const Node *const root,
    const std::vector<const Light *> &lights);

  Scene(
    const Node *const root,
    const std::vector<const Light *> &lights,
    const glm::dvec3 &ambient);

  // static const LightRay
  // constructRay(int x, int y, int width, int height);

  const Color getColor(const Ray &r) const;

private:
  Color getColorOfRayOnPhongMaterial(
    const PhongMaterial *material, 
    const Ray &rayFromEye,
    const GeometryIntersection &intersection) const;
};
