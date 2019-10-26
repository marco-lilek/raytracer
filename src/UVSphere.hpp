//
// Created by mllilek on 10/22/19.
//
#pragma once

#include "Sphere.hpp"
#include "Intersection.hpp"

struct UVSphere : public Sphere {
  Intersection intersect(const Ray &incomingRay) const override;

  bool isUV() const override {
    return true;
  }
};

