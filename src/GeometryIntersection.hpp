#pragma once

struct GeometryIntersection : public Object {
public:
  GeometryIntersection() : hit(false) {}
  GeometryIntersection(
      const Point &p,
      const Vector &n) : hit(true), p(p), n(n) {} 

  bool hit;

  // The point of intersection
  Point p;

  // The normal at the point of intersection
  Vector n;

  virtual const char * type() const {
    return "GeometryIntersection";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << "hit " << hit << " p " << p << " n " << n;
  }
};
