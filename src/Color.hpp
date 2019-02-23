#pragma once

#include <cstdint>
#include <glm/glm.hpp>

struct Color {
  const uint8_t r, g, b, a;
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : 
   r(r), g(g), b(b), a(a) {}

  Color(const glm::vec4 &f) : 
    r(encode(f[0])), 
    g(encode(f[1])), 
    b(encode(f[2])), 
    a(encode(f[3])) {}
  
  Color(float c) : 
    r(encode(c)), 
    g(encode(c)), 
    b(encode(c)), 
    a(encode(c)) {}

private:
  uint8_t encode(float v) {
    return v * 255;
  }
};