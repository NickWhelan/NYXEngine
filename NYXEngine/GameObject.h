#pragma once
#include "Model.h"
class GameObject
{
public:
	GLuint ShaderProgram;
	GameObject();
	GameObject(std::string _Name, std::string File, bool Primative);
	void Update();
	void Draw();
	void SetPosition(glm::vec3 _Position);
	glm::vec3 GetPosition();
	void SetRotation(glm::vec3 _Rotation);
	glm::vec3 GetRotation();
	~GameObject();
private:
	glm::vec3 *Position, *Rotation;
	Model* RenderModel;
	std::string Name;
	bool HasModel;
};

