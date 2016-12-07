#include "NYX.h"

#include "Model.h"

NYX::NYX()
{
	printf("Hello");
	window = new Window();
	window->WindowSetUp(0, 0);
	Model Thing;
	//Thing.LoadMesh("Pyramid");
	//game->window->setUpCamera(Thing.Render->Program);
}

NYX::~NYX()
{
}