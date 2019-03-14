#pragma once

#include <cstdint>
#include <glm/glm.hpp>

struct Color {
  const uint8_t r, g, b, a;
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
      : r(r), g(g), b(b), a(a)
  {
  }

  Color(const glm::dvec4 &f)
      : r(encode(f[0])), g(encode(f[1])), b(encode(f[2])),
        a(encode(f[3]))
  {
  }

  Color(double c) : Color(glm::dvec4(c)) {}

  // friend Color operator+ (Color& lhs,const Color& rhs) {
  //   return Color(lhs.r+rhs.r,lhs.g+rhs.g,lhs.b+rhs.b,
  //   lhs.a+rhs.a);
  // }

private:
  uint8_t
  encode(float v)
  {
    assert(v >= 0 && v <= 1);
    return v * 255;
  }
};
