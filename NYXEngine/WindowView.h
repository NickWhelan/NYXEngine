#pragma once
#include <stdio.h>
#include "OpenGL\include\glew.h"
#include <GL/glu.h>
#include <GL/gl.h>
// SDL headers
#include "SDL\Include\SDL.h"
#include "SDL\Include\SDL_main.h"
#include "SDL\Include\SDL_opengl.h"

class WindowView
{
public:
	WindowView();
	void WindowSetup(char Name[], float Width, float Height);
	void DestroyWindow();
	void ToggleFullScreen();
	~WindowView();
	
	SDL_Window* GetWindow();
	SDL_GLContext GetContext();
	SDL_Renderer* GetRenderer() const;
	
private:
	bool bIsFullScreen;
	SDL_GLContext glContext;
	SDL_Renderer* SDLRenderer;
	SDL_Window* window;
};

