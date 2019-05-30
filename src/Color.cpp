#include "Color.hpp"

std::array<uint8_t, 3> Color::toBytes() const {
  std::array<uint8_t, 3> asBytes;
  for (int i = 0; i < 3; i++) {
    asBytes[i] = enc(rgb[i]);
  }
  return asBytes;
}

uint8_t Color::enc(double v) const {
  const char * TRACE_HEADER = "Color::enc";
  int asInt = (int)(255 * v);
  Log::check(TRACE_HEADER, asInt >= 0 && asInt <= 255, "asInt {}", asInt);
  return asInt;
}
