#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>

#include "Object.hpp"

class Color : public Object {
public:
  glm::dvec4 rgba;
  Color(glm::dvec3 rgb)
      : rgba(rgb, 1)
  { }

  Color(double r, double g, double b)
      : rgba(r, g, b, 1)
  { }

  Color(double c) : Color(glm::dvec4(c,c,c,1)) {}

  std::array<uint8_t, 4> toBytes() {
    std::array<uint8_t, 4> asBytes;
    for (int i = 0; i < 4; i++) {
      asBytes[i] = enc(rgba[i]);
    }
    return asBytes;
  }

  virtual const char * type() const {
    return "Color";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    o << glm::to_string(rgba);
    return o;
  }

  // friend Color operator+ (Color& lhs,const Color& rhs) {
  //   return Color(lhs.r+rhs.r,lhs.g+rhs.g,lhs.b+rhs.b,
  //   lhs.a+rhs.a);
  // }
private:
  uint8_t enc(double v) {
    assert(v >= 0 && v <= 1);
    return 255 * v;
  }
};
