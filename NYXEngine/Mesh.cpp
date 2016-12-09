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
void Mesh::ImportMesh(std::string pFile) {
	const aiScene* scene = aiImportFile(pFile.c_str,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	if (scene->HasMeshes) {
		for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++)
			Vertices.push_back(glm::vec3(
				scene->mMeshes[0]->mVertices->x,
				scene->mMeshes[0]->mVertices->y,
				scene->mMeshes[0]->mVertices->z));
	}
	/*
	GLuint shaderUVs = glGetAttribLocation(programID, "vTexCoord");
	if (data.hasTexture)
	{
		glEnableVertexAttribArray(shaderUVs);
		glVertexAttribPointer(shaderUVs, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(vec3) * data.numVertices * 2));
		glBindTexture(GL_TEXTURE_2D, *(*gameObject)->textureId);
	}*/
}

Mesh::~Mesh() {
	Vertices.clear();
	Colors.clear();
}