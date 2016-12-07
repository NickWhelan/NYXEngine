#include "Model.h"

Model::Model() {
	mesh = new Mesh();
	Render = new Renderer();
	Render->SetupShader();
	Render->BufferSetUp(Render->Program);
}
void Model::LoadMesh() {}
void Model::LoadMesh(std::string Type) {
	mesh->MakePrinative(Type);
	Render->BindDataToBuffers(mesh);
}
void Model::Update() {
	Rotation.y += 0.0005;
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