#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <array>

#include "Constants.hpp"
#include "Log.hpp"
#include "Object.hpp"

class Color : public Object {
public:
  glm::dvec3 rgb;

  Color(glm::dvec3 rgb)
      : rgb(rgb)
  { }

  Color(double r, double g, double b)
      : rgb(r, g, b)
  { }

  Color(double c) : Color(glm::dvec3(c,c,c)) {}

  Color clamp() const {
    return Color(
        glm::clamp(rgb.x, 0.0, 1.0), 
        glm::clamp(rgb.y, 0.0, 1.0),
        glm::clamp(rgb.z, 0.0, 1.0));
  }

  std::array<uint8_t, 3> toBytes() const;

  virtual const char * type() const {
    return "Color";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    o << glm::to_string(rgb);
    return o;
  }

  void operator+=(const Color &o) {
    rgb += o.rgb;
  }

  friend Color operator+ (const Color& lhs ,const Color& rhs) {
    return lhs.rgb + rhs.rgb;
  }
  
  friend Color operator*(const Color&lhs, const Color&rhs) {
    return lhs.rgb * rhs.rgb;
  }

  bool operator>=(double v) const {
    return rgb.x >= v && rgb.y >= v && rgb.z >= v;
  }

private:
  uint8_t enc(double v) const;

};
