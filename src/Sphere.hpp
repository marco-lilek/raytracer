//
// Created by mllilek on 10/15/19.
//

#pragma once

#include "Geometry.hpp"

struct Sphere : public Geometry {

  Intersection intersect(const Ray &incomingRay) const override;
};

