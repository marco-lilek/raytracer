//
// Created by mllilek on 11/4/19.
//

#pragma once

#include <string>

namespace Obj {
  std::string fullPath(const std::string &name) {
    return "../assets/obj/" + name + ".obj";
  }
}
