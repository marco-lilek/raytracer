#pragma once

#include <vector>

#include <glm/glm.hpp>
#include "Color.hpp"
#include "Glm.hpp"

struct Light : public Object {
  const Glm::Vec3 color;
  const Glm::Vec4 pos;
  Light(const Glm::Vec3 &color, const Glm::Vec3 &pos)
      : color(color), pos(Glm::Vec4(pos,1))
  {
  }

  virtual const char * type() const {
    return "Light";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << pos;
  }
};

