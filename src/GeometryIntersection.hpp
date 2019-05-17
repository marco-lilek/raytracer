#pragma once

struct GeometryIntersection {
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
};
