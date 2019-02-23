/*
 * Node.cpp
 *
 *  Created on: Feb 20, 2019
 *      Author: mllilek
 */
#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>

#include "node/Node.hpp"

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

bool Node::intersect(const Ray &r, glm::vec4 &p, glm::vec4 &normal) const {
	Ray transRay(inv * r.from, inv * r.v);
	glm::vec4 localP;
	glm::vec4 localNormal;

	bool res =  intersectImpl(transRay, localP, localNormal);
	p = trans * localP;
	normal = localNormal * glm::transpose(inv);

	return res;
}

bool Node::intersectImpl(const Ray &r, glm::vec4 &p, glm::vec4 &normal) const {
	for (auto childIt = children.begin(); childIt != children.end(); ++childIt) {
		Node *child = *childIt;
		child->intersect(r, p, normal);
	}

	return false;
}

void Node::updateTrans(const glm::mat4 &mat) {
	trans = mat * trans;
	inv = glm::inverse(trans);
}