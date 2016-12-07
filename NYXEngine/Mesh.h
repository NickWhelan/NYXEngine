#pragma once
#include <stdio.h>
#include <vector>
#include <string>
//OpenGl
#include "glm\glm\glm.hpp"

class Mesh {
public:
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec3> Colors;
	Mesh();
	void setupMesh();
	void MakePrinative(std::string Type);
	~Mesh();
private:
	/*  Render data  */

};

