#include "SDL\Include\SDL.h"
#include "NYX.h"
#include "Model.h"
bool quit = false;
SDL_Event SDLEvent;
NYX* game;
Model* Thing;

void update() {
	switch (SDLEvent.type) {
	case SDL_EventType::SDL_QUIT:
		quit = true;
		break;
	}
}
void draw() {
	glClearColor(255, 0, 0, 255);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Thing->Draw();
	SDL_GL_SwapWindow(game->window->WindowView);
}

int main(int argc, char *argv[]) {
	game = new NYX();
	Thing = new Model();
	game->window->setSize(800, 400);
	Thing->LoadMesh("Pyramid");
	game->window->setUpCamera(Thing->Render->Program);
	game->window->MainCam->SetPosition(glm::vec3(0, 0, -10));
	game->window->setTitle("Test");
	while (!quit) {
		update();
		draw();
	}
	getchar();
	delete game;
	game = nullptr;
	return 0;
}