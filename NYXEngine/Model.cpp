#include "Model.h"

Model::Model(std::string _Name) {
	mesh = new Mesh();
	Render = new Renderer();
	Render->SetupShader();
	Render->BufferSetUp(Render->Program);
	Name = _Name;
	//Render->PositionSetup(Pos, Rotation);
}
void Model::LoadMesh() {}
void Model::LoadMesh(std::string Type) {
	mesh->MakePrinative(Type);
	Render->BindDataToBuffers(mesh);
}
void Model::Update() {
	//Rotation.y += 1;
	Render->Rotation.y += 0.001;
}
void Model::Draw() {
	Update();
	Render->Draw();
}
Model::~Model() {
	delete Render;
	Render = nullptr;
	delete mesh;
	mesh = nullptr;
}