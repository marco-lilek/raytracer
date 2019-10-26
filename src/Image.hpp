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
#include <glm/detail/type_vec.hpp>

class Image {
  std::vector<glm::dvec3> data;

public:
  const int width, height;
  Image(int width, int height) :
    width(width),
    height(height),
    data(width * height) {}

  void savePng(const std::string &fname);
  void draw(const glm::dvec3 &color, int x, int y);
};

#endif /* SRC_IMAGE_HPP_ */
