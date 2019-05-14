/*
 * Image.cpp
 *
 *  Created on: Feb 19, 2019
      Author: mllilek
 */

#include <array>
#include <lodepng/lodepng.h>

#include "Image.hpp"
#include "Log.hpp"

Image::Image(int width, int height)
  : width(width), height(height),
      data(width * height * 4, 0)
{
}

void
Image::render(const std::string &fname)
{
  const char *LOCATION = "Image::render";
  unsigned error =
    lodepng::encode(fname, data, width, height);
  if (error) {
    Log::error(LOCATION, "render error {}", lodepng_error_text(error));
    assert(0);
  }
}

void
Image::drawPixel(
  int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  int pos = (x + y * width) * 4;
  data[pos] = r;
  data[pos + 1] = g;
  data[pos + 2] = b;
  data[pos + 3] = a;
}

void Image::drawPixel(
  int x,
  int y,
  Color c)
{
  array<uint8_t, 4> asBytes = c.toBytes();

  int pos = (x + y * width) * 4;
  data[pos+0] = asBytes[0];
  data[pos+1] = asBytes[1];
  data[pos+2] = asBytes[2];
  data[pos+3] = asBytes[3];

}


Image::~Image() {}
