#include "Log.hpp"
#include "Texture.hpp"

using namespace Glm;

Vec3
Texture::getValue(double u, double v) const {
  const char * TRACE_HEADER = "Texture::getValue";
  Log::check(TRACE_HEADER, u >= 0.0 && u <= 1.0, "range u {}", u);
  Log::check(TRACE_HEADER, v >= 0.0 && v <= 1.0, "range v {}", v);
  int x = u * width;
  int y = v * height;

  return data[y * width + x];
}
