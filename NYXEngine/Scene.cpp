#include "Scene.h"

Scene::Scene()
{
	Models = new std::vector<Model>();
}

void Scene::AddModel(Model _Model) {
	Models->push_back(_Model);
}
void  Scene::AddGameObject(GameObject _GameObject) {
	GameObjects->push_back(_GameObject);
}
Model*  Scene::GetModel(std::string Name) {
	return &Models->at(0);
	for (int i = 0; i < Models->size()-1; i++) {
		if (Models->at(i).Name == Name) {
			return &Models->at(i);
		}
	}
}

Scene::~Scene()
{
	Models->clear();
	delete Models;
	Models = nullptr;
	GameObjects->clear();
	delete GameObjects;
	GameObjects = nullptr;
}
