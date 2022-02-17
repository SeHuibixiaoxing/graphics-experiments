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
	glm::vec3 position;					// 位置
	glm::vec3 normal;					// 法向
	glm::vec2 texCoords;				// 纹理坐标
	glm::vec3 tangent;
	glm::vec3 bitangent;

	GLint m_BoneIDs[MAX_BONE_INFLUENCE];
	GLfloat m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
	GLuint id;							// 纹理ID 
	std::string type;					// 纹理类型
	std::string path;					
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, GLint drawMode);
	void Draw(Shader shader);					// 使用shader绘制该Mesh

private:
	std::vector<Vertex> vertices;				// 顶点数据
	std::vector<GLuint> indices;				// 索引数据
	std::vector<Texture> textures;				// 纹理数据
	GLuint VBO, EBO, VAO;
	void setupMesh(GLint drawMode);
};

