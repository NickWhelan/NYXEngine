#include "pch.h"
#include "Controller.h"


Controller::Controller()
{
}

void Controller::AddController(int CdeviceID) {
	if (SDL_IsGameController(CdeviceID)) {
		controller = SDL_GameControllerOpen(CdeviceID);
		if (controller)
			return ;
		else
			printf("Could not open gamecontroller %i: %s\n", CdeviceID, SDL_GetError());
	}
}
void Controller::RemoveController(int CdeviceID) {
	SDL_GameControllerClose(controller);
	delete controller;
	controller = nullptr;
}

