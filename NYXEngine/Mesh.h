#pragma once
#include <stdio.h>
#include <vector>
#include <string>
//OpenGl
#include "glm\glm\glm.hpp"
//asimp
//#include "assimp\Importer.hpp"
#include "assimp\cimport.h"
#include "assimp\scene.h"
#include "assimp\postprocess.h"

class Mesh {
public:
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec3> Colors;
	Mesh();
	void ImportMesh(std::string pFile);
	void MakePrinative(std::string Type);
	~Mesh();
private:
	/*  Render data  */

};

