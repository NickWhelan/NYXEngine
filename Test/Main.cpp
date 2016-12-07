#include "SDL\Include\SDL.h"
#include "NYX.h"
#include "Model.h"
bool quit;
SDL_Event SDLEvent;
NYX* game;
int main(int argc, char *argv[]) {
	game = new NYX();
	game->window->setSize(800, 400);
	

	while (!quit) {
		switch (SDLEvent.type) {
		case SDL_EventType::SDL_QUIT:
			quit = true;
			break;
		}
		glClearColor(0, 0, 0, 0);
		//Thing.Draw();
	}
	getchar();
	delete game;
	game = nullptr;
	return 0;
}