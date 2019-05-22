#pragma once

#include "Intersection.hpp"

struct GeometryIntersection : public Object, public Intersection {
  // where the fired ray is positioned relative to the geometry
  enum ShooterPos {
    Miss, // (shooter)/^ object
    Past, // (object) (shooter)----->
    Inside, // (object (shooter)---)--->
    Towards, // (shooter)----->(object)
  };

  GeometryIntersection(ShooterPos sp) : 
    shooterPos(sp),
    p(Point()),
    n(Vector()) {}

  GeometryIntersection(const ShooterPos sp,
      const Point &p,
      const Vector &n) : 
    shooterPos(sp), 
    p(p),
    n(n) {} 

  virtual bool isHit() const {
    return Inside == shooterPos || Towards == shooterPos;
  }

  // TODO private+getters since these should not be mutable
  // The point of intersection
  Point p;

  // The normal at the point of intersection
  Vector n;

  virtual const char * type() const {
    return "GeometryIntersection";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    return o << "shooterPos " << shooterPos << " p " << p << " n " << n;
  }

  ShooterPos shooterPos;
};
