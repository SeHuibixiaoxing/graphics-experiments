#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include <iostream>

#include "shader.h"


constexpr auto MAX_BONE_INFLUENCE = 4;

struct Vertex
{
	glm::vec3 position;					// λ��
	glm::vec3 normal;					// ����
	glm::vec2 texCoords;				// ��������
	glm::vec3 tangent;
	glm::vec3 bitangent;

	GLint m_BoneIDs[MAX_BONE_INFLUENCE];
	GLfloat m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
	GLuint id;							// ����ID 
	std::string type;					// ��������
	std::string path;					
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, GLint drawMode);
	void Draw(Shader shader);					// ʹ��shader���Ƹ�Mesh

private:
	std::vector<Vertex> vertices;				// ��������
	std::vector<GLuint> indices;				// ��������
	std::vector<Texture> textures;				// ��������
	GLuint VBO, EBO, VAO;
	void setupMesh(GLint drawMode);
};

