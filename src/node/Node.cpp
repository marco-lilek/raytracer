/*
 * Node.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: mllilek
 */
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <algorithm>

#include "node/Node.hpp"
#include "Material.hpp"

using namespace glm;

Node::Node(const std::string &name) : name(name), trans(1), inv(1) {
}

Node::~Node() {
  // TODO
}

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

void Node::scale(const glm::vec3& amount) {
	updateTrans(glm::scale(amount));
}

void Node::translate(const glm::vec3& amount) {
	updateTrans(glm::translate(amount));
}

const Material *Node::intersect(const Ray &r, glm::vec4 &p, glm::vec4 &normal) const {
	Ray transRay(inv * r.from, inv * r.v);
	glm::vec4 localP;
	glm::vec4 localNormal;

	const Material *res = intersectImpl(transRay, localP, localNormal);
	p = trans * localP;
	normal = inv * localNormal;

	return res;
}

const Material *Node::intersectImpl(const Ray &r, glm::vec4 &p, glm::vec4 &normal) const {
	const Material *toRet = nullptr;
	float closestDistance = 0;
	glm::vec4 bestp;
	glm::vec4 bestnormal;

	for (auto childIt = children.begin(); childIt != children.end(); ++childIt) {
		Node *child = *childIt;
		glm::vec4 thisp;
		glm::vec4 thisnormal;
		const Material *fromChild = child->intersect(r, thisp, thisnormal);

		if (fromChild) {
			float thisDistance = std::max(0.0f, glm::distance(thisp, r.from));
			if (toRet == nullptr || thisDistance < closestDistance) {
				toRet = fromChild;
				bestp = thisp;
				bestnormal = thisnormal;
			}
		}
	}

	p = bestp;
	normal = bestnormal;

	return toRet;
}

void Node::updateTrans(const glm::mat4 &mat) {
	trans = mat * trans;
	inv = glm::inverse(trans);
}