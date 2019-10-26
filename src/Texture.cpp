//
// Created by mllilek on 10/22/19.
//

#include <lodepng.h>
#include "Texture.hpp"

namespace {
  double decodeColor(uint8_t v) {
    return (double)v / 255.0;
  }
}

glm::dvec3 Texture::getValue(double u, double v) const {
  int x = u * width;
  int y = v * height;
  return data[y * width + x];
}

Texture::Texture(const std::string &name, const std::string &texture) {
  // TODO don't hard code the path
  std::string filename = std::string("../assets/textures/") + texture + ".png";
  std::vector<unsigned char> image; //the raw pixels

  unsigned width, height;
  unsigned error = lodepng::decode(image, width, height, filename);
  // TODO check errors

  int NUM_BYTES_PER_PIXEL = 4;
  int numPixels = width * height;

  this->width = width;
  this->height = height;
  data.resize(width * height);

  double x,y,z;
  for (int i = 0; i < numPixels; i++) {
    int sidx = i*NUM_BYTES_PER_PIXEL;
    x = decodeColor(image[sidx+0]);
    y = decodeColor(image[sidx+1]);
    z = decodeColor(image[sidx+2]);
    this->data[i] = glm::dvec3(x,y,z);
    //Log::trace("sdf", "i {} data {}", i, data);
  }
}
