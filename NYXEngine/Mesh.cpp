#include "Mesh.h"
Mesh::Mesh() {}

void Mesh::MakePrinative(std::string Type) {
	if (Type == "Cube") {
		//Front
		Vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0));
		Vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0));
		Vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0));
		Vertices.push_back(glm::vec3(1.0f, 0.0f, 0.0));

		//Back
		Vertices.push_back(glm::vec3(0.0f, 0.0f, 1.0));
		Vertices.push_back(glm::vec3(0.0f, 1.0f, 1.0));
		Vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0));
		Vertices.push_back(glm::vec3(1.0f, 0.0f, 1.0));

		//Left
		Vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0));
		Vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0));
		Vertices.push_back(glm::vec3(0.0f, 1.0f, 1.0));
		Vertices.push_back(glm::vec3(0.0f, 0.0f, 1.0));

		//Right
		Vertices.push_back(glm::vec3(1.0f, 0.0f, 0.0));
		Vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0));
		Vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0));
		Vertices.push_back(glm::vec3(1.0f, 0.0f, 1.0));

		//bottom
		Vertices.push_back(glm::vec3(0.0f, 0.0f, 0.0));
		Vertices.push_back(glm::vec3(1.0f, 0.0f, 0.0));
		Vertices.push_back(glm::vec3(1.0f, 0.0f, 1.0));
		Vertices.push_back(glm::vec3(0.0f, 0.0f, 1.0));

		//Top
		Vertices.push_back(glm::vec3(0.0f, 1.0f, 0.0));
		Vertices.push_back(glm::vec3(1.0f, 1.0f, 0.0));
		Vertices.push_back(glm::vec3(1.0f, 1.0f, 1.0));
		Vertices.push_back(glm::vec3(0.0f, 1.0f, 1.0));

		Colors.push_back(glm::vec3(0, 0, 0));
		Colors.push_back(glm::vec3(0, 0, 0));
		Colors.push_back(glm::vec3(0, 0, 0));
		Colors.push_back(glm::vec3(0, 0, 0));

		Colors.push_back(glm::vec3(1, 1, 1));
		Colors.push_back(glm::vec3(1, 1, 1));
		Colors.push_back(glm::vec3(1, 1, 1));
		Colors.push_back(glm::vec3(1, 1, 1));

		Colors.push_back(glm::vec3(1, 0, 1));
		Colors.push_back(glm::vec3(1, 0, 1));
		Colors.push_back(glm::vec3(1, 0, 1));
		Colors.push_back(glm::vec3(1, 0, 1));

		Colors.push_back(glm::vec3(1, 1, 0));
		Colors.push_back(glm::vec3(1, 1, 0));
		Colors.push_back(glm::vec3(1, 1, 0));
		Colors.push_back(glm::vec3(1, 1, 0));

		Colors.push_back(glm::vec3(0, 1, 0));
		Colors.push_back(glm::vec3(0, 1, 0));
		Colors.push_back(glm::vec3(0, 1, 0));
		Colors.push_back(glm::vec3(0, 1, 0));

		Colors.push_back(glm::vec3(1, 0, 0));
		Colors.push_back(glm::vec3(1, 0, 0));
		Colors.push_back(glm::vec3(1, 0, 0));
		Colors.push_back(glm::vec3(1, 0, 0));
	}
	else if (Type == "Pyramid") {
		//front
		Vertices.push_back(glm::vec3(0, 1, 0.5));
		Vertices.push_back(glm::vec3(1, -1, 0));
		Vertices.push_back(glm::vec3(-1, -1, 0));
		//right
		Vertices.push_back(glm::vec3(0, 1, 0.5));
		Vertices.push_back(glm::vec3(1, -1, 0));
		Vertices.push_back(glm::vec3(0, -1, 1));
		//left
		Vertices.push_back(glm::vec3(0, 1, 0.5));
		Vertices.push_back(glm::vec3(-1, -1, 0));
		Vertices.push_back(glm::vec3(0, -1, 1));

		Colors.push_back(glm::vec3(0, 0, 0));
		Colors.push_back(glm::vec3(0, 0, 0));
		Colors.push_back(glm::vec3(0, 0, 0));
		Colors.push_back(glm::vec3(1, 1, 1));
		Colors.push_back(glm::vec3(1, 1, 1));
		Colors.push_back(glm::vec3(1, 1, 1));
		Colors.push_back(glm::vec3(0, 1, 0));
		Colors.push_back(glm::vec3(0, 1, 0));
		Colors.push_back(glm::vec3(0, 1, 0));
	}
}
void Mesh::setupMesh() {}

Mesh::~Mesh() {
	Vertices.clear();
	Colors.clear();
}