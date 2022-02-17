#include "Node.h"

Node::Node(GLfloat* vertices, GLuint size)
{
	this->setupBox(vertices, size);
}

void Node::insertChild(Node* child)
{
	this->child.push_back(child);
}

void Node::translate(glm::vec3 trans)
{
	this->box.translate(trans);
}

void Node::rotate(GLfloat angle, glm::vec3 axis)
{
	this->box.rotate(angle, axis);
}

void Node::zoom(glm::vec3 scaling)
{
	this->box.zoom(scaling);
}

void Node::setTranslate(glm::vec3 trans)
{
	this->box.setTranslate(trans);
}

void Node::setRotate(GLfloat angle, glm::vec3 axis)
{
	this->box.setRotate(angle, axis);
}

void Node::setZoom(glm::vec3 scaling)
{
	this->box.setZoom(scaling);
}

void Node::draw(Shader shader)
{
	draw(this, glm::mat4(1.0f), shader);
}

void Node::draw(Node* now, glm::mat4 modelPre, Shader& shader)
{
	if (now == nullptr) return;
	glm::mat4 modelNow = modelPre * now->box.getModel().getCompositeExceptZoom();
	for (auto next : now->child)
	{
		draw(next, modelNow, shader);
	}
	now->box.setModelMat4(modelNow * now->box.getModel().getZoom());
	now->box.draw(shader);	

	return;
}


void Node::setupBox(GLfloat* vertices, GLuint size)
{
	this->box.setupBox(vertices, size);
}