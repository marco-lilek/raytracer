#pragma once

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>

#include "Object.hpp"

class Color : public Object {
public:
  glm::dvec3 rgb;

  Color(glm::dvec3 rgb)
      : rgb(rgb)
  { }

  Color(double r, double g, double b)
      : rgb(r, g, b)
  { }

  Color(double c) : Color(glm::dvec3(c,c,c)) {}

  std::array<uint8_t, 3> toBytes() {
    std::array<uint8_t, 3> asBytes;
    for (int i = 0; i < 3; i++) {
      asBytes[i] = enc(rgb[i]);
    }
    return asBytes;
  }

  virtual const char * type() const {
    return "Color";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    o << glm::to_string(rgb);
    return o;
  }

  void operator+=(const Color &o) {
    rgb += o.rgb;
  }

  friend Color operator+ (const Color& lhs ,const Color& rhs) {
    return lhs.rgb + rhs.rgb;
  }
  
  friend Color operator*(const Color&lhs, const Color&rhs) {
    return lhs.rgb * rhs.rgb;
  }

private:
  uint8_t enc(double v) {
    assert(v >= 0 && v <= 1);
    return 255 * v;
  }

};
