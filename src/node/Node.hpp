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

class Node {
  std::string name;
  std::vector<Node *> children;

  glm::mat4 trans;

public:
  Node(const std::string &name);
  virtual ~Node();

  void rotate(char axis, float angle);
  void scale(const glm::vec3& amount);
  void translate(const glm::vec3& amount);

  virtual bool intersect(const Ray &r, float &t, glm::vec4 &normal) const;
};

#endif /* SRC_NODE_NODE_H_ */
