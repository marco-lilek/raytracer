#pragma once

#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "Intersection.hpp"
#include "Material.hpp"
#include "Ray.hpp"

class Node : public Object {
  std::vector<Node *> children;

  // M
  glm::mat4 modelTransform;

  // M^-1
  glm::mat4 invModelTransform;

  // (M^-1)^T
  glm::mat4 invTransModelTransform;

public:
  std::string name;

  Node(const std::string &name);
  virtual ~Node();

  void rotate(char axis, float angle);
  void scale(const glm::dvec3 &amount);
  void translate(const glm::dvec3 &amount);

  void updateModelTransform(const glm::mat4 &mat);

  void
  addChild(Node *child)
  {
    children.push_back(child);
  }

  const Intersection intersect(const Ray &r) const;
  virtual const Intersection intersectImpl(const Ray &r) const;

  virtual const char * type() const {
    return "Node";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    // For the sake of brevity avoid dumping the full node tree
    return o << "name: " << name 
      << " modelTransform: " << glm::to_string(modelTransform);
  }
};
