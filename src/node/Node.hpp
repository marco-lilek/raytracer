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
#include "material/Material.hpp"

class Node {
  std::vector<Node *> children;

  glm::mat4 trans;
  glm::mat4 inv;

public:
  std::string name;

  Node(const std::string &name);
  virtual ~Node();

  void rotate(char axis, float angle);
  void scale(const glm::dvec3& amount);
  void translate(const glm::dvec3& amount);

  void updateTrans(const glm::mat4 &mat);

  void addChild(Node *child) {
    children.push_back(child);
  }

  const Material *intersect(const Ray &r,
                            glm::dvec4 &p,
                            glm::dvec4 &normal
                            ) const;

  virtual const Material * _intersect(const Ray &r,
                                      glm::dvec4 &p,
                                      glm::dvec4 &normal
                                      ) const;
};

#endif /* SRC_NODE_NODE_H_ */
