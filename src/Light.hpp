#pragma once

#include <vector>

#include <glm/glm.hpp>
#include "Point.hpp"

struct Light : public Object {
  const glm::dvec3 color;
  const Point pos;
  Light(const glm::dvec3 &color, Point pos)
      : color(color), pos(pos)
  {
  }

  virtual const char * type() const {
    return "Light";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    o << "color " << glm::to_string(color) << " pos ";
    pos.dump(o);
    return o;
  }
};

