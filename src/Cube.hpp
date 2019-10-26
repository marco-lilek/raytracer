//
// Created by mllilek on 10/15/19.
//

#pragma once

#include "Geometry.hpp"

struct Cube : public Geometry {
  virtual Intersection intersect(const Ray &incomingRay) const;
};


