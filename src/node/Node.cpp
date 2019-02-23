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

Node::Node(const std::string &name) : name(name) {
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
	mat4 rot_matrix = glm::rotate(glm::radians(angle), rot_axis);
}

void Node::scale(const glm::vec3& amount) {
}

void Node::translate(const glm::vec3& amount) {
}

bool Node::intersect(const Ray &r, float &t, glm::vec4 &normal) const {
	for (auto childIt = children.begin(); childIt != children.end(); ++childIt) {
		// TODO: apply translations
		(*childIt)->intersect(r, t, normal);
	}
}