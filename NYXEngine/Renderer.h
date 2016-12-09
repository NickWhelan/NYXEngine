#pragma once
#include <iostream>
#include <vector>

#include "OpenGL\include\glew.h"

#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"

//Shaders
//#include "Shader.h"
#include "LoadShaders.h"
#include "Mesh.h"
//OpenGl

static const int NumberOfBuffers = 2;
class Renderer
{
public:
	GLuint Buffers[NumberOfBuffers];
	GLuint VBO, VAO, Program, modelMatrix;
	glm::mat4 modelOrigin;
	glm::vec3 Position, Rotation;

	int BufferLength=0;
	Renderer();
	void  BufferSetUp(GLuint const Program);
	//void  BindDataToBuffers(std::vector<glm::vec3>* Points, std::vector<glm::vec3>* Colors);
	void  BindDataToBuffers(Mesh* mesh);
	void  SetupShader();
	void PositionSetup(glm::vec3 _Position, glm::vec3 _Rotation);
	void Update();
	void Draw();
	~Renderer();
};

