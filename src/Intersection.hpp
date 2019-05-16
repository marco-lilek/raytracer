#pragma once

#include "Point.hpp"
#include "Vector.hpp"

// Forward declare because of circular dependency
class Node;

// TODO Could avoid wasting stack space when we have 
// an intersection that didn't hit
// ...but for now this is good enough, better than using the heap
// (so we can keep things running fast)
struct Intersection {

  Intersection(Node *hitNode,
      const Point &p,
      const Vector &n) : 
    hitNode(hitNode),
    p(p),
    n(n) {}

  Intersection() : hitNode(nullptr) {}

  // The node that we hit
  Node *hitNode;

  // The point of intersection
  Point p;

  // The normal at the point of intersection
  Vector n;
};
