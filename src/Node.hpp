#pragma once

#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "Intersection.hpp"
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

  const Intersection intersect(const Ray &r) const;
  virtual const Intersection intersectImpl(const Ray &r) const;
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
