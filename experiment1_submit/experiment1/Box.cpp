#include "Box.h"

Box::Box()
{
}

Box::Box(GLfloat* vertices, GLuint size)
{
	this->setupBox(vertices, size);
}

void Box::draw(Shader shader)
{
	shader.use();
	shader.setInt("material.diffuse", 0);
	shader.setInt("material.specular", 1);

	shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	shader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
	shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	shader.setFloat("light.constant", 1.0f);
	shader.setFloat("light.linear", 0.0014f);
	shader.setFloat("light.quadratic", 0.000007f);

	shader.setFloat("material.shininess", 32.0f);


	//auto model_now_mat = model.getComposite();
	auto model_now_mat = this->modelMat4;
	shader.setMat4("model", model_now_mat);
	shader.setMat4("normModel", glm::transpose(glm::inverse(model_now_mat)));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);


	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Box::loadTexture(const char* const diffusePath, const char* const specularPath)
{
	diffuseMap = Box::loadTexture(diffusePath);
	specularMap = Box::loadTexture(specularPath);
}

void Box::translate(glm::vec3 trans)
{
	this->model.setTranslate(glm::translate(this->model.getTranslate(), trans));
}

void Box::rotate(GLfloat angle, glm::vec3 axis)
{
	this->model.setRotate(glm::rotate(this->model.getRotate(), angle, axis));
}

void Box::zoom(glm::vec3 scaling)
{
	this->model.setZoom(glm::scale(this->model.getZoom(), scaling));
}

void Box::setTranslate(glm::vec3 trans)
{
	this->model.setTranslate(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
	this->translate(trans);
}

void Box::setRotate(GLfloat angle, glm::vec3 axis)
{
	this->model.setRotate(glm::quat(1, 0, 0, 0));
	this->rotate(angle, axis);
}

void Box::setZoom(glm::vec3 scaling)
{
	this->model.setZoom(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)));
	this->zoom(scaling);
}

void Box::setupBox(GLfloat* vertices, GLuint size)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	//坐标
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//法向
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

ModelMat Box::getModel()
{
	return this->model;
}

void Box::setModel(ModelMat _model)
{
	this->model = _model;
}

void Box::setModelMat4(glm::mat4 _modelMat4)
{
	this->modelMat4 = _modelMat4;
}

GLuint Box::loadTexture(const char* const path)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	GLint width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}


GLuint Box::diffuseMap = 0;
GLuint Box::specularMap = 0;