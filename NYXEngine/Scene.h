#pragma once
#include "GameObject.h"
#include <string>
class Scene
{
public:
	Scene();
	void AddModel(Model _Model);
	void AddGameObject(GameObject _GameObject);
	Model* GetModel(std::string Name);

	~Scene();
private:
	std::vector<Model>* Models;
	std::vector<GameObject> *GameObjects;
	//std::vector<Texture> Textures;
};

