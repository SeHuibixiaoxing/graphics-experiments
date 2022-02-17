#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


GLuint TextureFromFile(const GLchar* path, const std::string& directory, GLboolean gamma = false);

class Model
{
public:
    Model(std::string const& path, GLint drawMode, GLboolean gamma = false);
    void Draw(Shader& shader);

private:
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;

    GLboolean gammaCorrection;

    void loadModel(std::string const& path, GLint drawMode);
    void processNode(aiNode* node, const aiScene* scene, GLint drawMode);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene, GLint drawMode);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

