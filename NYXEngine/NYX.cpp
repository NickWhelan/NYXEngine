#include "NYX.h"

#include "Model.h"

NYX::NYX()
{
	printf("Started NYX\n");
	window = Window::GetInstance();
	window->WindowSetUp(800, 400);
}

NYX::~NYX()
{
}