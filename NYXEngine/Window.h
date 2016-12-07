#pragma once
#include <stdio.h>
#include <string>
#include "Renderer.h"
#include "Camera.h"

//Open Gl
#include "OpenGL\include\glew.h"

#include "glm\glm\glm.hpp"
#include "SDL\Include\SDL.h"
#include "SDL\Include\SDL_opengl.h"
class Window
{
public:
	
	SDL_GLContext WindowGlContext;
	SDL_Renderer* SDLWindowRenderer;
	SDL_Window* WindowView;
	Camera* MainCam;
	float WIDTH, HEIGHT;

	Window();
	static Window* GetInstance();
	void WindowSetUp(float _Width, float _Height);
	void setUpCamera(GLuint Program);
	void setSize(float _Width,float _Height);
	void setTitle(std::string Title);
	void setFullScreen();
	~Window();
private:
	static Window* Instance;
};

