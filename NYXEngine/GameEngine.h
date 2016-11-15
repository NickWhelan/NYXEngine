#pragma once
#include "WindowView.h"
#include "Controller.h"
#include "SDL\Include\SDL_gamecontroller.h"
#include "SDL\Include\SDL.h"
#include "OpenGLRenderer.h"
#include <iostream>

class GameEngine
{
public:
	SDL_Event SDLEvent;
	Controller *Controllers[8];
	WindowView* Window;
	OpenGLRenderer* Renderer;

	bool quit = false;
	
	GameEngine();
	void GameLoop();
	void Update();
	void Draw();
	void Quit();
	~GameEngine();
};

