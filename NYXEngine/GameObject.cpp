#include "GameObject.h"
GameObject::GameObject()
{
	Position = new glm::vec3(0, 0, 0);
	Rotation = new glm::vec3(0, 0, 0);
}
GameObject::GameObject(std::string _Name, std::string File, bool Primative) {
	Name = _Name;
	RenderModel = new Model(Name);
	if (RenderModel != NULL)
	{
		HasModel = true;
		if (Primative == true) {
			RenderModel->LoadMesh(File);
		}
		ShaderProgram = RenderModel->Render->Program;
		//Position = &RenderModel->Pos;
		//Rotation = &RenderModel->Rotation;
	}
}
void GameObject::Update() {
	RenderModel->Pos = *Position;
	RenderModel->Rotation = *Rotation;
}
void GameObject::Draw() {
	RenderModel->Draw();
}

void GameObject::SetPosition(glm::vec3 _Position) {
	Position = &_Position;
	RenderModel->Pos = _Position;
	RenderModel->Render->Position = _Position;
}

GameObject::~GameObject()
{
	delete Position;
	Position = nullptr;
	delete Rotation;
	Rotation = nullptr;
	delete RenderModel;
	RenderModel = nullptr;
}
