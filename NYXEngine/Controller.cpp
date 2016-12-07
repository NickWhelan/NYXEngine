#include "Controller.h"



Controller::Controller(int id)
{
	if (SDL_IsGameController(id)) {
		pad = SDL_GameControllerOpen(id);
		if (pad) {
			joy = SDL_GameControllerGetJoystick(pad);
			ID = SDL_JoystickInstanceID(joy);
		}
	}
}


Controller::~Controller()
{
}
