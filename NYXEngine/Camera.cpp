#include "Camera.h"
#include <stdio.h>


Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, GLuint program)
{
	Position = position;
	Direction = lookAt;
	Up = up;
	cameraMatrix = glGetUniformLocation(program, "view_matrix");
	projMatrixLoc = glGetUniformLocation(program, "projection_matrix");
	Persepective(45.0f, 1.777778f, 0.1f, 10000.0f);
	SetPosition(position);
	LookAt(lookAt);
}
void Camera::Persepective(float fov, float aspect, float nearPlane, float farPlane) {
	Projection = glm::perspective(fov, aspect, nearPlane, farPlane);
	glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &Projection[0][0]);
}

void Camera::SetPosition(glm::vec3 Point) {
	Position = Point;
	View = glm::translate(glm::mat4(1.0), Position);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &View[0][0]);
	printf("CamPos: X:%f,Y:%f,Z:%f\n", Position.x, Position.y, Position.z);
}
void Camera::MoveCamera(glm::vec3 Offset) {
	Position.x += Offset.x;
	Position.y += Offset.y;
	Position.z += Offset.z;
	View = glm::translate(glm::mat4(1.0), Position);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &View[0][0]);
}
void Camera::LookAt(glm::vec3 Point) {
	/*
	glm::vec3 loc = cameratranslateVal;
	glm::vec3 dir = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cam_mat = glm::lookAt(loc, dir, up);
	*/
	Direction = Point;
	//	glm::vec3 look = Direction+Point;
	glm::vec3 look = glm::vec3(0,0,0);
	View = glm::lookAt(Position, look, Up);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &View[0][0]);
	printf("CamLook: X:%f,Y:%f,Z:%f\n", look.x, look.y, look.z);
}

Camera::~Camera()
{
}
