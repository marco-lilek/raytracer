#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <fmt/format.h>

struct Light {
  const glm::dvec3 color;
  const glm::dvec4 pos;
  Light(const glm::dvec3 &color, glm::dvec3 pos)
      : color(color), pos(glm::dvec4(pos, 1))
  {
  }
};

template <>
struct fmt::formatter<Light> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(const Light &o, FormatContext &ctx) {
    return format_to(ctx.out(), "[Light {} {}]", o.color, o.pos);
  }
};

