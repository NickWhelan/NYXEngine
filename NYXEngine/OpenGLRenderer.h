#pragma once
#include "AbstractRenderer.h"
#include <vector>
#include "OpenGL\include\glew.h"
#include "OpenGL\include\glut.h"
#include "vgl.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "LoadShaders.h"
#include "Camera.h"

class OpenGLRenderer :
	public AbstractRenderer
{

public:
	OpenGLRenderer();
	~OpenGLRenderer();

	enum VAO_IDs { Triangles, NumVAOs };
	enum Buffer_IDs { ArrayBuffer, NumBuffers };
	enum Attrib_IDs { vPosition = 0 };

	GLuint VAOs[NumVAOs];
	GLuint Buffers[NumBuffers];
	float CamDist = 1;
	GLuint location, location2, location3;
	Camera* CameraOne;

	void PreRender();
	void PostRender();
	void renderPrimitive(PRIMITIVETYPE prim);
};

