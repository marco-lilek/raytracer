#pragma once

#include "Color.hpp"
#include "Light.hpp"
#include "Object.hpp"
#include "GeometryIntersection.hpp"
#include "ReflectiveMaterial.hpp"
#include "TextureMaterial.hpp"
#include "Glm.hpp"
#include "Ray.hpp"
#include <vector>

class Node;
class PhongMaterial;

struct Scene : public Object {
  const Node *const root;
  const std::vector<const Light *> lights;
  Glm::Vec3 ambientLight;

  // const glm::dvec3 fireRay(const LightRay &r) const;
  const Glm::Vec3 getColor(const Ray &r, int depth) const;

public:
  Scene(
    const Node *const root,
    const std::vector<const Light *> &lights);

  Scene(
    const Node *const root,
    const std::vector<const Light *> &lights,
    const Glm::Vec3 &ambient);

  // static const LightRay
  // constructRay(int x, int y, int width, int height);

  const Glm::Vec3 getColor(const Ray &r) const;

  virtual const char * type() const;

  virtual std::ostream& dump(std::ostream& o) const;

private:
  Glm::Vec3 getColorOfRayOnPhongMaterial(
    const PhongMaterial *material, 
    const Ray &rayFromEye,
    const GeometryIntersection &intersection) const;

  Glm::Vec3 getColorOfRayOnReflectiveMaterial(
    const ReflectiveMaterial *material, 
    const Ray &rayFromEye,
    const GeometryIntersection &intersection,
    const int depth) const;
};
