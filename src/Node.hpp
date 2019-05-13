/*
 * Node.h
 *
 *  Created on: Feb 20, 2019
 *      Author: mllilek
 */

#ifndef SRC_NODE_NODE_H_
#define SRC_NODE_NODE_H_

#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "Material.hpp"
#include "Ray.hpp"

class Node {
  std::vector<Node *> children;

  glm::mat4 trans;
  glm::mat4 inv;

public:
  std::string name;

  Node(const std::string &name);
  virtual ~Node();

  void rotate(char axis, float angle);
  void scale(const glm::dvec3 &amount);
  void translate(const glm::dvec3 &amount);

  void updateTrans(const glm::mat4 &mat);

  void
  addChild(Node *child)
  {
    children.push_back(child);
  }

  const Node *intersect(
    const Ray &r, glm::dvec4 &p, glm::dvec4 &normal) const;

  virtual const Node *_intersect(
    const Ray &r, glm::dvec4 &p, glm::dvec4 &normal) const;

  virtual glm::dvec3
  getColor(
    const Scene &scene,
    const LightRay &incomingRay,
    const glm::dvec4 &sceneHit,
    const glm::dvec4 &sceneHitNormal) const
  {
    throw std::logic_error("called getColor on Node");
  }
};

template <>
struct fmt::formatter<Node> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(const Node &n, FormatContext &ctx) {
    return format_to(ctx.out(), "[Node {}]", n.name);
  }
};

#endif /* SRC_NODE_NODE_H_ */
