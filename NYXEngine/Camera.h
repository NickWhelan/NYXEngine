#pragma once
#include "OpenGL\include\glew.h"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\matrix_transform.hpp"
class Camera
{
public:
	glm::mat4 Projection,View;
	glm::vec3 Position, Direction, Up,Rotation, MoveDirection;
	GLuint Shader;
	GLuint cameraMatrix, projMatrixLoc;
	Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, GLuint program);
	void Persepective(float fov, float aspect, float nearPlane, float farPlane);
	void MoveCamera(glm::vec3 Offset);
	void SetPosition(glm::vec3 Point);
	void LookAt(glm::vec3 Point);
	void SetFrustum(float Left,float Right,float Bottom, float Top,float Near, float Far);
	void Rotate();
	void FPSCamera();
	~Camera();
};

