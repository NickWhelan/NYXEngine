#include "Camera.h"
#include <stdio.h>


Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up, GLuint program)
{
	Position = position;
	Direction = lookAt;
	Up = up;
	Shader = program;
	cameraMatrix = glGetUniformLocation(Shader, "view_matrix");
	projMatrixLoc = glGetUniformLocation(Shader, "projection_matrix");
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
	//printf("CamPos: X:%f,Y:%f,Z:%f\n", Position.x, Position.y, Position.z);
}
void Camera::Rotate() {
	float x = glm::cos(Rotation.x);
	float z = glm::sin(Rotation.x);
	float YA = glm::cos(Rotation.y);
	float y = glm::sin(Rotation.y);
	LookAt(glm::vec3(x * YA, -y, z * YA));
}
void Camera::SetFrustum(float Left, float Right, float Bottom, float Top, float Near, float Far) {
	Projection = glm::frustum(Left, Right, Bottom, Top, Near, Far);
	glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &Projection[0][0]);
}

void Camera::MoveCamera(glm::vec3 Offset) {
	Position.x += Offset.x;
	Position.y += Offset.y;
	Position.z += Offset.z;
	View = glm::translate(glm::mat4(1), Position);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &View[0][0]);
}
void Camera::LookAt(glm::vec3 Point) {
	Direction = Point;
	glm::vec3 look = Position+Direction;
	View = glm::lookAt(Position, look, Up);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &View[0][0]);
}

void Camera::FPSCamera() {
	float x = glm::cos(Rotation.x);
	float z = glm::sin(Rotation.x);
	float YA = glm::cos(Rotation.y);
	float y = glm::sin(Rotation.y);
	Direction = glm::vec3(x * YA, -y, z * YA);
	glm::vec3 look = Position + Direction;
	View = glm::lookAt(Position, look, Up);
	View += glm::translate(View, glm::normalize(Direction) * MoveDirection);
	glUniformMatrix4fv(cameraMatrix, 1, GL_FALSE, &View[0][0]);
	MoveDirection = glm::vec3(0, 0, 0);
}

Camera::~Camera()
{
}
