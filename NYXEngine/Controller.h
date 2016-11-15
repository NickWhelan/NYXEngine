#pragma once
#include <stdio.h>
#include "SDL\Include\SDL_gamecontroller.h"
class Controller
{
public:
	Controller();
	SDL_GameController* controller;
	void AddController(int CdeviceID);
	void RemoveController(int CdeviceID);
	~Controller();
};

