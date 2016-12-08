#include "SDL\Include\SDL.h"
#include "NYX.h"
#include "Model.h"
bool quit = false;
SDL_Event SDLEvent;
NYX* game;
Window * window;
Model* Thing;

void update() {
	switch (SDLEvent.type) {
	case SDL_EventType::SDL_QUIT:
		quit = true;
		break;
	case SDL_KEYDOWN:
		printf("%c\n",SDLEvent.key.keysym.sym);
	}
}
void draw() {
	glClearColor(0.5, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Thing->Draw();
	glFlush();
	SDL_GL_SwapWindow(game->window->WindowView);
}

int main(int argc, char *argv[]) {
	game = new NYX();
	Thing = new Model();
	window = game->window;
	window->setSize(800, 400);
	Thing->LoadMesh("Pyramid");
	window->setUpCamera(Thing->Render->Program);
	window->MainCam->SetPosition(glm::vec3(0, 0, -10));
	window->MainCam->LookAt(glm::vec3(0, 0, 0));
	window->setTitle("Test");
	while (!quit) {
		update();
		draw();
	}
	getchar();
	delete game;
	game = nullptr;
	return 0;
}