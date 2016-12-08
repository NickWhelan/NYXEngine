#include "NYX.h"

#include "Model.h"

NYX::NYX()
{
	printf("Started NYX");
	window = Window::GetInstance();
	window->WindowSetUp(0, 0);
}

NYX::~NYX()
{
}