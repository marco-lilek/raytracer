#pragma once

#include <stdexcept>
#include <string>
#include <vector>
#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "Ray.hpp"
#include "Intersection.hpp"

class Node {
public:
  std::string name;

  Node(const std::string &name) :
  name(name),
  modelTransform(1),
  invModelTransform(1),
  invTransModelTransform(1) {}

  virtual ~Node() {}

  void rotate(char axis, float angle);
  void scale(glm::dvec3 scale);
  void translate(glm::dvec3 translation);
  void addChild(Node *child);

  Intersection intersect(const Ray &incomingRay) const;
private:
  virtual Intersection intersectImpl(const Ray &incomingRay) const;

  std::vector<Node *> children;

  // M
  glm::dmat4 modelTransform;

  // M^-1
  glm::dmat4 invModelTransform;

  // (M^-1)^T
  glm::dmat4 invTransModelTransform;

  void updateModelTransform(const glm::dmat4 &mat);

};
