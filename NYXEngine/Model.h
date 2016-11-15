#pragma once
#include "glm\glm\glm.hpp"
#include "OpenGL\include\glew.h"
#include "OpenGL\include\glut.h"
#include "glm\glm\gtc\matrix_transform.hpp"

#include "LoadShaders.h"
class Model
{
public:
	enum PrimitiveShapes {
		Cube,
		Rect,
		Primide,
		Primide2
	};
	Model();
	glm::mat4 Poisition;
	void MakeShape(PrimitiveShapes Type);
	void MakeShape(glm::vec3 P_Verts[], glm::vec3 P_ColorData[]);
	void LoadBuffer(ShaderInfo shaders[]);
	void Draw(GLuint location);
	glm::vec3 Verts [255];
	glm::vec3 ColorData [255];
private:
};

