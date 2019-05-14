#pragma once

#include <ostream>
#include <fmt/format.h>

class Object {
public:
  virtual const char* type() const = 0;
  virtual std::ostream& dump(std::ostream& o) const = 0;
};

std::ostream& operator<<(std::ostream& o, const Object& b);

template <>
struct fmt::formatter<Object> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

  template <typename FormatContext>
  auto format(const Object &o, FormatContext &ctx) {
    return format_to(ctx.out(), o);
  }
};
