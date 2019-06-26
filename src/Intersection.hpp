#pragma once

struct Intersection : public Object {
  // where the fired ray is positioned relative to the target
  enum ShooterPos {
    Miss, // (shooter)/^ object
    Past, // (object) (shooter)----->
    Inside, // (object (shooter)---)--->
    Towards, // (shooter)----->(object)
  };

  ShooterPos shooterPos;

  Intersection(const ShooterPos &sp) : 
    shooterPos(sp) {}

  virtual bool isHit() const {
    return Inside == shooterPos || Towards == shooterPos;
  }

  virtual const char * type() const {
    return "Intersection";
  }

  virtual std::ostream& dump(std::ostream& o) const {
    static const char *ShooterPosStr[] = {
        "Miss",
        "Past",
        "Inside",
        "Towards"
    };
    return o << "shooterPos " << ShooterPosStr[shooterPos];
  }
};
