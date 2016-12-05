#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

#include <OpenGL\include\glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
//#include <SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Simple OpenGL Image Library\src\SOIL.h>
#include "Mesh.h"

GLint TextureFromFile(const char* path, string directory);

class Model {
public:
	//Functions
	//Constructor, looking for a file path to a model.
	Model(GLchar* path);

	//Draws the model, and the meshes
	//void Draw(Shader shader);
private:

	//Model Dats
	vector<Mesh> meshes;
	string directory;
	
	//Stores all loaded textures so far
	//optimization to make sure textures aren't loaded more than once
	vector<Texture> textures_loaded;

	//Functions
	//Loads a model with supported ASSIMP extensions from file
	//stores resulting meshes in meshes vector.
	void loadModel(string path);

	//Processes a node in a recursive fashion.
	//Processes each individual mesh located at the node
	//and repeats this process on its children node(if any)
	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	
};
