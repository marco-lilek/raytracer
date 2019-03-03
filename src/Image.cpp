/*
 * Image.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mllilek
 */

#include <lodepng/lodepng.h>
#include <loguru/loguru.hpp>

#include "Image.hpp"

Image::Image(int width, int height) :
  width(width),
  height(height),
  data(width * height * 4, 0) {}

void Image::render(const std::string& fname) {
  unsigned error = lodepng::encode(fname, data, width, height);
  if (error) {
    DLOG_F(INFO, "Render error %s", lodepng_error_text(error));
  }
}

void Image::drawPixel(
    int x, int y,
    uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  int pos = (x + y * width) * 4;
  data[pos] = r;
  data[pos+1] = g;
  data[pos+2] = b;
  data[pos+3] = a;
}

Image::~Image() {
}
