#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Light {
	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

class Shader
{
public:
	// �ֱ��ȡ������������ɫ����Ƭ����ɫ��
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	
	// ������ɫ��
	void use();

	void setShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void setShader(const std::string& vertexCode, const std::string& fragmentCode);

	// ����uniform����
	void setBool(const std::string& name, GLboolean value) const;
	void setInt(const std::string& name, GLint value) const;
	void setFloat(const std::string& name, GLfloat value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;
	void setVec3(const std::string& name, const glm::vec3& value) const;
	void setVec3(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const;

	//��ȡid
	GLuint getID() const;
private:
	// program object id
	GLuint ID;
};

