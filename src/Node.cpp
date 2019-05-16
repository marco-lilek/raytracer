/*
 * Node.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: mllilek
 */
#include <algorithm>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <fmt/format.h>

#include "Debug.hpp"
#include "Material.hpp"
#include "Node.hpp"
#include "Intersection.hpp"

using namespace glm;
using namespace std;

Node::Node(const std::string &name) : 
  name(name), 
  modelTransform(1),
  invModelTransform(1),
  invTransModelTransform(1)
{
}

Node::~Node() {}

void
Node::rotate(char axis, float angle)
{
  vec3 rot_axis;

  switch (axis) {
  case 'x': rot_axis = vec3(1, 0, 0); break;
  case 'y': rot_axis = vec3(0, 1, 0); break;
  case 'z': rot_axis = vec3(0, 0, 1); break;
  default: break;
  }
  mat4 rot = glm::rotate(glm::radians(angle), rot_axis);
  updateModelTransform(rot);
}

void
Node::scale(const glm::dvec3 &amount)
{
  updateModelTransform(glm::scale(amount));
}

void
Node::translate(const glm::dvec3 &amount)
{
  updateModelTransform(glm::translate(amount));
}

const Intersection Node::intersect(const Ray &r) const
{
  const char *METHOD_NAME = "Node::intersect";
  Log::trace(METHOD_NAME, "*this: {} r: {}", *this, r);

  // Applying the model transformations M
  //
  // For some point p in the model space
  // Mp is p in the world space
  // 
  // So for some point q in the world space 
  // inverse(M)q is q in the model space
  Ray rayInModelSpace(glm::dvec4(invModelTransform * r.from),
      glm::dvec4(invModelTransform * r.v));

  const Intersection intersectionInModelSpace = 
    intersectImpl(rayInModelSpace);

  // By similar reasoning, we have to apply the model transformations
  // on all outgoing vectors/points in the model space to return them to
  // the world space
  //
  // The normal at the point of intersection is different:
  // for normal n and any two points P1 P2 on a model, in the model space
  // n^T (P2-P1) = 0
  //
  // so suppose we want this to hold in the world space, with points M P1, M P2
  // let n' be the normal in the world space, (N n)
  // (n')^T ((M P2) - (M P1))
  // = (N n)^T M (P2 - P1)
  // = n^T N^T M (P2 - P1)
  // = n^T (N^T M) (P2 - P1)
  //
  // so as long as N^T := M^-1 then we'd have
  // = n^T I (P2 - P1) = 0
  // as required
  //
  // So n' = N n = (M^-1)^T n

  // Also note the node we ultimately hit does not change
  Intersection intersectionInWorldSpace(
      intersectionInModelSpace.hitNode,
      glm::dvec4(modelTransform * intersectionInModelSpace.p),
      glm::dvec4(invTransModelTransform * intersectionInModelSpace.n));

  return intersectionInWorldSpace;
}

const Intersection Node::intersectImpl(const Ray &r) const
{
  return Intersection();
  // const Node *toRet = nullptr;
  // double closestDistance = 0;
  // glm::dvec4 bestp;
  // glm::dvec4 bestnormal;
  // // cerr << "intersect !" << r.v << endl;

  // for (auto childIt = children.begin();
  //      childIt != children.end();
  //      ++childIt) {
  //   Node *child = *childIt;

  //   // cerr << "child " << child->name <<endl;
  //   glm::dvec4 thisp;
  //   glm::dvec4 thisnormal;
  //   // cerr << "r.p, r.v" << r.from << " " << r.v << endl;
  //   const Node *fromChild =
  //     child->intersect(r, thisp, thisnormal);

  //   if (fromChild) {
  //     // cerr << fromChild->name <<endl;
  //     double thisDistance =
  //       std::max(0.0, glm::distance(thisp, r.from));
  //     // cerr << thisDistance << endl;
  //     if (
  //       toRet == nullptr ||
  //       thisDistance < closestDistance) {
  //       toRet = fromChild;
  //       bestp = thisp;
  //       bestnormal = thisnormal;
  //       closestDistance = thisDistance;
  //     }
  //   }
  // }

  // p = bestp;
  // normal = bestnormal;

  // // if (toRet) cerr << "ya it hit" << endl;
  // if (toRet) {
  //   Log::debug("best {}", toRet->name);
  // } else {
  //   Log::debug("no best");
  // }

  // return toRet;
}

void
Node::updateModelTransform(const glm::mat4 &mat)
{
  modelTransform = mat * modelTransform;
  invModelTransform = glm::inverse(modelTransform);

  // Keep only the upper 3x3 portion of the matrix since this is the only part
  // pertinent for vectors
  invTransModelTransform = glm::mat4(
      glm::transpose(glm::mat3(invModelTransform)));
}

