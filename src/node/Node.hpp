/*
 * Node.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mllilek
 */

#ifndef SRC_NODE_NODE_H_
#define SRC_NODE_NODE_H_

#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Ray.hpp"
#include "Material.hpp"

class Node {
  std::string name;
  std::vector<Node *> children;

  glm::mat4 trans;
  glm::mat4 inv;

public:
  Node(const std::string &name);
  virtual ~Node();

  void rotate(char axis, float angle);
  void scale(const glm::vec3& amount);
  void translate(const glm::vec3& amount);
  void updateTrans(const glm::mat4 &mat);

  const Material *intersect(const Ray &r, glm::vec4 &p, glm::vec4 &normal) const;

  virtual const Material *intersectImpl(const Ray &r, glm::vec4 &p, glm::vec4 &normal) const;
};

#endif /* SRC_NODE_NODE_H_ */
