/*
 * Image.hpp
 *
 *  Created on: Feb 19, 2019
 *      Author: mllilek
 */

#ifndef SRC_IMAGE_HPP_
#define SRC_IMAGE_HPP_

#include <cstdint>
#include <string>
#include <vector>

#include "Color.hpp"

class Image {
  std::vector<uint8_t> data;

public:
  int width, height;
  Image(int width, int height);

  void render(const std::string &fname);
  void drawPixel(
    int x,
    int y,
    uint8_t r,
    uint8_t g,
    uint8_t b,
    uint8_t a);

  void drawPixel(
    int x,
    int y,
    uint8_t r,
    uint8_t g,
    uint8_t b);

  void drawPixel(
    int x,
    int y,
    Color c);

  virtual ~Image();
};

#endif /* SRC_IMAGE_HPP_ */
