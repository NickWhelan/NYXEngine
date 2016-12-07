#pragma once
#include "SDL\Include\SDL_gamecontroller.h"
#include "SDL\Include\SDL.h"
class Controller
{
public:
	SDL_GameController *pad;
	SDL_Joystick *joy;
	int ID;

	Controller(int id);
	void RemoveController(int id);
	void OnControllerButton(const SDL_ControllerButtonEvent sdlEvent);
	void OnControllerAxis(const SDL_ControllerAxisEvent sdlEvent);
	~Controller();
};

