/*
 * Node.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: mllilek
 */
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <algorithm>
#include <iostream>

#include "node/Node.hpp"
#include "material/Material.hpp"
#include "Debug.hpp"

using namespace glm;
using namespace std;

Node::Node(const std::string &name) :
  name(name),
  trans(1),
  inv(1)
{}

Node::~Node() {}

void Node::rotate(char axis, float angle) {
	vec3 rot_axis;

	switch (axis) {
		case 'x':
			rot_axis = vec3(1,0,0);
			break;
		case 'y':
			rot_axis = vec3(0,1,0);
	        break;
		case 'z':
			rot_axis = vec3(0,0,1);
	        break;
		default:
			break;
	}
	mat4 rot = glm::rotate(glm::radians(angle), rot_axis);
	updateTrans(rot);

}

void Node::scale(const glm::dvec3& amount) {
	updateTrans(glm::scale(amount));
}

void Node::translate(const glm::dvec3& amount) {
	updateTrans(glm::translate(amount));
}

const Node *Node::intersect(const Ray &r,
                                glm::dvec4 &p,
                                glm::dvec4 &normal
                                ) const {
  Log::debug("trying {}", name);
  // cerr << "wrapper" << endl;
  // cerr << glm::to_string(inv) << endl;
	Ray transRay(inv * r.from, inv * r.v);
	glm::dvec4 localP;
	glm::dvec4 localNormal;

	const Node *res = _intersect(transRay, localP, localNormal);
	p = trans * localP;
	normal = inv * localNormal;

	return res;
}

const Node * Node::_intersect(const Ray &r,
                                  glm::dvec4 &p,
                                  glm::dvec4 &normal
                                  ) const {
	const Node *toRet = nullptr;
	double closestDistance = 0;
	glm::dvec4 bestp;
	glm::dvec4 bestnormal;
        // cerr << "intersect !" << r.v << endl;

	for (auto childIt = children.begin(); childIt != children.end(); ++childIt) {
		Node *child = *childIt;

                // cerr << "child " << child->name <<endl;
		glm::dvec4 thisp;
		glm::dvec4 thisnormal;
                // cerr << "r.p, r.v" << r.from << " " << r.v << endl;
		const Node * fromChild = child->intersect(r, thisp, thisnormal);

		if (fromChild) {
                  // cerr << fromChild->name <<endl;
			double thisDistance = std::max(0.0, glm::distance(thisp, r.from));
                        // cerr << thisDistance << endl;
			if (toRet == nullptr || thisDistance < closestDistance) {
				toRet = fromChild;
				bestp = thisp;
				bestnormal = thisnormal;
				closestDistance = thisDistance;
			}
		}
	}

	p = bestp;
	normal = bestnormal;

        // if (toRet) cerr << "ya it hit" << endl;
        if (toRet) {
            Log::debug("best {}", toRet->name);
        } else {
            Log::debug("no best");
        }

	return toRet;
}

void Node::updateTrans(const glm::mat4 &mat) {
	trans = mat * trans;
	inv = glm::inverse(trans);
}
