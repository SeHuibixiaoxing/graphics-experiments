#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image.h>

#include <string>
#include <vector>
#include <iostream>

#include "shader.h"
#include "ModelMat.h"

class Box
{
public:
	Box();
	Box(GLfloat* vertices, GLuint size);
	void draw(Shader shader);
	static GLuint diffuseMap, specularMap;

	void static loadTexture(const char* const diffusePath, const char* const specularPath);
	GLuint VBO, VAO;

	void translate(glm::vec3 trans);
	void rotate(GLfloat angle, glm::vec3 axis);
	void zoom(glm::vec3 scaling);
	void setTranslate(glm::vec3 trans);
	void setRotate(GLfloat angle, glm::vec3 axis);
	void setZoom(glm::vec3 scaling);

	void setupBox(GLfloat* vertices, GLuint size);

	ModelMat getModel();
	void setModel(ModelMat _model);

	void setModelMat4(glm::mat4 _modelMat4);
private: 
	ModelMat model;
	glm::mat4 modelMat4;
	GLuint static loadTexture(const char* const path);

};

