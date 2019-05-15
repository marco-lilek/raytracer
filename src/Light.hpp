#pragma once

#include <vector>

#include <glm/glm.hpp>
#include "Color.hpp"
#include "Point.hpp"

struct Light : public Object {
  const Color color;
  const Point pos;
  Light(const Color &color, const Point &pos)
      : color(color), pos(pos)
  {
  }

  virtual const char * type() const {
    return "Light";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    o << "color: " << color << " pos: " << pos;
    return o;
  }
};

