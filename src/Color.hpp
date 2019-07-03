#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>

#include "Constants.hpp"
#include "Log.hpp"
#include "Object.hpp"
#include "Glm.hpp"

namespace Color {
  std::array<uint8_t, 3> toBytes(const Glm::Vec3 &c);

  double decode(uint8_t v);
  uint8_t enc(double v);
};

