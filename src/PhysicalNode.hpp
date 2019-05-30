#pragma once

#include <glm/glm.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "PhysicalIntersection.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Node.hpp"

class PhysicalNode : public Node {
public:
  const Material *material;
  PhysicalNode(const std::string &name, const Material *material) : 
    Node(name), material(material) {}

  virtual const char * type() const {
    return "PhysicalNode";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    Node::dump(o);
    o << "material: ";
    if (material != nullptr) {
      o << *material;
    }

    return o;
  }
};
