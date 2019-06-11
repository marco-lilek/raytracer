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
#include "PhysicalIntersection.hpp"

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

void Node::dumpNodeTree(std::ostream &o) const {
  o << *this << " ";
  for (int i = 0; i < children.size(); i++) {
    children[i]->dumpNodeTree(o);
  }
}

void
Node::rotate(char axis, float angle)
{
  const char *TRACE_HEADER = "Node::rotate";
  vec3 rot_axis;

  switch (axis) {
  case 'x': rot_axis = vec3(1, 0, 0); break;
  case 'y': rot_axis = vec3(0, 1, 0); break;
  case 'z': rot_axis = vec3(0, 0, 1); break;
  default:
    Log::check(TRACE_HEADER, false, "axis {} angle {}", axis, angle);
    break;
  }
  mat4 rot = glm::rotate(glm::radians(angle), rot_axis);
  //Log::info(TRACE_HEADER, "rot {}", glm::to_string(rot));
  updateModelTransform(rot);
}

void
Node::scale(double x, double y, double z)
{
  updateModelTransform(glm::scale(glm::dvec3(x,y,z)));
}

void
Node::translate(double x, double y, double z)
{
  updateModelTransform(glm::translate(glm::dvec3(x,y,z)));
}

const PhysicalIntersection Node::intersect(const Ray &incomingRay) const
{
  const char *METHOD_NAME = "Node::intersect";
  Log::trace(METHOD_NAME, "this: {}", *this);
  Log::trace(METHOD_NAME, "incomingRay: {}", incomingRay);

  // Applying the model transformations M
  //
  // For some point p in the model space
  // Mp is p in the world space
  // 
  // So for some point q in the world space 
  // inverse(M)q is q in the model space
  Ray rayInModelSpace(glm::dvec4(invModelTransform * incomingRay.from),
      glm::dvec4(invModelTransform * incomingRay.v));

  const PhysicalIntersection intersectionInModelSpace = 
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

  if (!intersectionInModelSpace.isHit()) {
    return PhysicalIntersection();
  }

  // Also note the node we ultimately hit does not change
  const GeometryIntersection &intersectionInModelSpaceGeometry = 
    intersectionInModelSpace.geometry;
  GeometryIntersection intersectionInWorldSpaceGeometry(
      intersectionInModelSpaceGeometry.shooterPos,
      glm::dvec4(modelTransform * intersectionInModelSpaceGeometry.p),
      // TODO use the invTrans correctly
      glm::dvec4(invTransModelTransform * intersectionInModelSpaceGeometry.n));

  PhysicalIntersection intersectionInWorldSpace(
      intersectionInModelSpace.hitNode, 
      intersectionInWorldSpaceGeometry);

  return intersectionInWorldSpace;
}

const PhysicalIntersection Node::intersectImpl(const Ray &r) const
{
  const char * METHOD_NAME = "Node::intersectImpl";
  // For a node, we need to return the intersection 
  // from the child node with the closest point of intersection

  // Default init we have no hit
  PhysicalIntersection closestIntersection;

  // Since the distance is always positive we can use -1 to prime the loop
  double closestDistance = -1;

  for (auto childIt = children.begin(); 
      childIt != children.end();
      ++childIt) {
    Node *child = *childIt;

    PhysicalIntersection intersectionFromChild = child->intersect(r);
    if (intersectionFromChild.hitNode == nullptr) {
      continue;
    } else {
      double thisDistance = r.from.distanceTo(intersectionFromChild.geometry.p);
      if (closestDistance == -1 || thisDistance <= closestDistance) {
        Log::trace(METHOD_NAME, "thisDistance {} closestDistance {}",
           thisDistance, closestDistance); 
        // Kinda stinky: we need to copy off the intersection
        // every time we have a decent hit
        // ...still faster than using the heap?
        closestIntersection = intersectionFromChild;
        closestDistance = thisDistance;
      }
    }
  }

  Log::trace(METHOD_NAME, "closestIntersection {}", closestIntersection);

  return closestIntersection;
}

void
Node::updateModelTransform(const glm::dmat4 &mat)
{
  modelTransform = mat * modelTransform;
  glm::mat3 inv3x3(glm::inverse(glm::mat3(modelTransform)));
  invModelTransform = glm::inverse(modelTransform);

  // Keep only the upper 3x3 portion of the matrix since this is the only part
  // pertinent for vectors
  invTransModelTransform = glm::mat4(glm::transpose(inv3x3));
}

