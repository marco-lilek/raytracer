#pragma once

#include "Color.hpp"
#include "Light.hpp"
#include "LightRay.hpp"
#include "Object.hpp"
#include "GeometryIntersection.hpp"
#include "ReflectiveMaterial.hpp"
#include "TextureMaterial.hpp"
#include <vector>

class Node;
class PhongMaterial;

struct Scene : public Object {
  const Node *const root;
  const std::vector<const Light *> lights;
  glm::dvec3 ambientLight;

  // const glm::dvec3 fireRay(const LightRay &r) const;
  const Color getColor(const Ray &r, int depth) const;

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

  virtual const char * type() const;

  virtual std::ostream& dump(std::ostream& o) const;

private:
  Color getColorOfRayOnPhongMaterial(
    const PhongMaterial *material, 
    const Ray &rayFromEye,
    const GeometryIntersection &intersection) const;

  Color getColorOfRayOnReflectiveMaterial(
    const ReflectiveMaterial *material, 
    const Ray &rayFromEye,
    const GeometryIntersection &intersection,
    const int depth) const;
};
