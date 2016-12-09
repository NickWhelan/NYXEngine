#include "Scene.h"

Scene::Scene()
{
}

void Scene::AddModel(Model _Model) {
	Models->push_back(_Model);
}
void  Scene::AddGameObject(GameObject _GameObject) {
	GameObjects->push_back(_GameObject);
}
Model*  Scene::GetModel(std::string Name) {

	for (int i = 0; i < Models->size(); i++) {
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
