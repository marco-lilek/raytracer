#include "Color.hpp"

using namespace Glm;

std::array<uint8_t, 3> Color::toBytes(const Vec3 &v) {
  std::array<uint8_t, 3> asBytes;
  for (int i = 0; i < 3; i++) {
    asBytes[i] = enc(v[i]);
  }
  return asBytes;
}

double Color::decode(uint8_t v) {
  const char * TRACE_HEADER = "Color::enc";
  double asDouble = ((double)v) / 255.0;
  return asDouble;
}

uint8_t Color::enc(double v) {
  const char * TRACE_HEADER = "Color::enc";
  int asInt = (int)(255 * v);
  Log::check(TRACE_HEADER, asInt >= 0 && asInt <= 255, "asInt {}", asInt);
  return asInt;
}
