#include "PrimitiveNode.hpp"

Cube PrimitiveNode::cube;
Sphere PrimitiveNode::sphere;

Geometry *
PrimitiveNode::getGeometryFromType(const std::string &type) const {
  const char *METHOD_NAME = "PrimitiveNode::getGeometryFromType";
  if (type == "cube") {
    return &cube;
  } else if (type == "sphere") {
    return &sphere;
  } else {
    Log::error(METHOD_NAME, "got invalid type {}", type);
  }
}
