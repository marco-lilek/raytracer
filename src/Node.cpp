//
// Created by mllilek on 10/15/19.
//

#include <glm/gtx/transform.hpp>
#include <iostream>
#include "Node.hpp"
#include "maths.hpp"
#include "constants.hpp"
#include "Log.hpp"

void Node::rotate(char axis, float angle) {
  glm::vec3 rot_axis;

  switch (axis) {
    case 'x': rot_axis = glm::dvec3(1, 0, 0); break;
    case 'y': rot_axis = glm::dvec3(0, 1, 0); break;
    case 'z': rot_axis = glm::dvec3(0, 0, 1); break;
    default:
      break;
  }
  glm::mat3 rot = glm::rotate(glm::radians(angle), rot_axis);
  updateModelTransform(glm::dmat4(rot));
}

void Node::scale(glm::dvec3 scale) {
  updateModelTransform(glm::scale(scale));
}

void Node::translate(glm::dvec3 translation) {
  updateModelTransform(glm::translate(translation));
}

void Node::addChild(Node *child) {
  children.push_back(child);
}

void Node::updateModelTransform(const glm::dmat4 &mat) {
  modelTransform = mat * modelTransform;
  glm::mat3 inv3x3(glm::inverse(glm::mat3(modelTransform)));
  invModelTransform = glm::inverse(modelTransform);

  // Keep only the upper 3x3 portion of the matrix since this is the only part
  // pertinent for vectors
  invTransModelTransform = glm::mat4(glm::transpose(inv3x3));
}

Intersection Node::intersect(const Ray &incomingRay) const {
  // Applying the model transformations M
  //
  // For some point p in the model space
  // Mp is p in the world space
  //
  // So for some point q in the world space
  // inverse(M)q is q in the model space
  Ray rayInModelSpace(
          glm::dvec4(invModelTransform * incomingRay.p),
          glm::dvec4(invModelTransform * incomingRay.v));

  Intersection intersection = intersectImpl(rayInModelSpace);

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

  if (!intersection.isHit()) {
    return intersection;
  }

  intersection.p = glm::dvec4(modelTransform * intersection.p);
  intersection.n = glm::dvec4(invTransModelTransform * intersection.n);

  //if (UVIntersection *uvIntersection =
  //            dynamic_cast<UVIntersection *>(geometry)) {
  //  uvIntersection->t = glm::dvec4(
  //          invTransModelTransform * uvIntersection->t);
  //}
  return intersection;
}

Intersection Node::intersectImpl(const Ray &incomingRay) const {
  // For a node, we need to return the intersection
  // from the child node with the closest point of intersection

  // Since the distance is always non-negative we can use -1 to prime the loop
  double closestDistance = -1;

  Intersection closestIntersection;

  for (auto childIt = children.begin();
       childIt != children.end();
       ++childIt) {
    Node *child = *childIt;

    Intersection childIntersection = child->intersect(incomingRay);
    if (!childIntersection.isHit()) {
      continue;
    } else {
      double thisDistance = maths::distance3d(
              incomingRay.p, childIntersection.p);
      // Too close, probably just caused by numerical error,
      // so we wont consider it an intersection
      if (closestDistance == -1 || thisDistance <= closestDistance) {
        closestIntersection = childIntersection;
        closestDistance = thisDistance;
      }
    }
  }

  return closestIntersection;
}

