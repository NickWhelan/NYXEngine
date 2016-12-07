#pragma once
#include <string>
#include "Mesh.h"
#include "Renderer.h"
class Renderer;
class Model
{
public:
	Mesh* mesh;
	GLuint VAO;
	Renderer* Render;
	glm::vec3 Pos, Rotation;
	int start,Length;
	

	Model();
	void LoadMesh();
	void LoadMesh(std::string Type);
	void Update();
	void Draw();
	~Model();
private:
};