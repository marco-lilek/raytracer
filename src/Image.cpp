//
// Created by mllilek on 10/15/19.
//

#include <spdlog/spdlog.h>
#include <lodepng.h>
#include <glm/glm.hpp>
#include "Image.hpp"

using namespace std;

namespace {
  uint8_t convert(double d) {
    return (uint8_t)(255.0 * glm::clamp(d, 0.0, 1.0));
  }

};

void Image::savePng(const std::string &fname) {
  std::vector<uint8_t> encoded(width * height * 4);
  for (int i = 0; i < data.size(); i++) {
    glm::dvec3 colour = data[i];
    encoded[i*4] = convert(colour.x);
    encoded[i*4+1] = convert(colour.y);
    encoded[i*4+2] = convert(colour.z);
    encoded[i*4+3] = convert(1.0);
  }

  unsigned error = lodepng::encode(fname, encoded, width, height);
  if (error) {
    spdlog::error("render error {}", lodepng_error_text(error));
    assert(0);
  }
}

void Image::draw(const glm::dvec3 &color, int x, int y) {
  data[y * width + x] = color;
}

