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

Node::Node(const std::string &name)
    : name(name), trans(1), inv(1)
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
  updateTrans(rot);
}

void
Node::scale(const glm::dvec3 &amount)
{
  updateTrans(glm::scale(amount));
}

void
Node::translate(const glm::dvec3 &amount)
{
  updateTrans(glm::translate(amount));
}

const Intersection Node::intersect(const Ray &r) const
{
  return Intersection();
  //const char *METHOD_NAME = "Node::intersect";
  //Log::trace(METHOD_NAME, "*this: {} r: {}", *this, r);

  //// Applying the model transformations M
  ////
  //// For some point p in the model space
  //// Mp is p in the world space
  //// 
  //// So for some point q in the world space 
  //// inverse(M)q is q in the model space
  //Ray rayInModelSpace(inv * r.from, inv * r.v);

  //const Intersection intersectionInModelSpace = 
  //  _intersect(rayInModelSpace);

  //// By similar reasoning, we have to apply the model transformations
  //// on all outgoing vectors/points in the model space to return them to
  //// the world space
  ////
  //// TODO: the reasoning for the normal is not the same though
  //Intersection intersectionInWorldSpace(
  //    trans * intersectionInModelSpace.p,
  //    trans * intersectionInModelSpace.n);

  //return intersectionInWorldSpace;
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
Node::updateTrans(const glm::mat4 &mat)
{
  trans = mat * trans;
  inv = glm::inverse(trans);
}

