#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <glm\glm\glm.hpp>
#include <glm\glm\gtc\matrix_transform.hpp>
#include <OpenGL\include\glew.h>
#include <assimp\types.h>

using namespace std;

struct Vertex {
	//Position
	glm::vec3 Position;

	//Normal
	glm::vec3 Normal;

	//Tex Coords
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh
{
public:
	//Mesh Data
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures; 



	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	
	//Don't have the Shader for this yet
	//void Draw(Shader shader);

	~Mesh();

private: 

	//Render Data
	GLuint VAO, VBO, EBO;

	//Functions
	void setupMesh();
};

