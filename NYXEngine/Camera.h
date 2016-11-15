#pragma once
#include "glm\glm\gtc\matrix_transform.hpp"
class Camera
{
public:
	Camera();
	glm::mat4 *camera_matrix, *projection_matrix;
	float CamDist;
	void RenderCam();
};

