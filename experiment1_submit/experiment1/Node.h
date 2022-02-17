#pragma once

#include "Box.h"
#include <vector>
#include <stack>

class Node
{
public:
	Node(GLfloat* vertices, GLuint size);
	void insertChild(Node* child);

	void translate(glm::vec3 trans);
	void rotate(GLfloat angle, glm::vec3 axis);
	void zoom(glm::vec3 scaling);

	void setTranslate(glm::vec3 trans);
	void setRotate(GLfloat angle, glm::vec3 axis);
	void setZoom(glm::vec3 scaling);

	void draw(Shader shader);

	Box box;

private:
	std::vector<Node*> child;

	void setupBox(GLfloat* vertices, GLuint size);
	void draw(Node* now, glm::mat4 modelPre, Shader& shader);
};

