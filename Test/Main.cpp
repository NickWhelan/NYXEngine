#include "SDL\Include\SDL.h"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "NYX.h"
#include "Scene.h"
#include "GameObject.h"

bool quit = false;
SDL_Event SDLEvent;
NYX* game;
Window * window;
Camera* MainCam;
//Scene* MainScene;
//Model* Thing;
GameObject *Thing1, *Thing2, *Thing3;

int MouseX, MouseY;
const float  MouseSensitivity = 0.001;
float Delta = 0.66;

void update() {
	while (SDL_PollEvent(&SDLEvent))
	{
		switch (SDLEvent.type) {
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			//printf("%c\n", SDLEvent.key.keysym.sym);
			if (SDLEvent.key.keysym.sym == '`') {
				quit = true;
			}
			if (SDLEvent.key.keysym.sym == 'w') {
				MainCam->MoveCamera(glm::vec3(0, 0, 0.1));
				//MainCam->MoveDirection.z = 20;
			}
			else if (SDLEvent.key.keysym.sym == 's') {
				MainCam->MoveCamera(glm::vec3(0, 0, -0.1));
				//MainCam->MoveDirection.z = -20;
			}
			if (SDLEvent.key.keysym.sym == 'a') {
				MainCam->MoveCamera(glm::vec3(0.1, 0, 0));
				//MainCam->MoveDirection.z = 20;
			}
			else if (SDLEvent.key.keysym.sym == 'd') {
				MainCam->MoveCamera(glm::vec3(-0.1, 0,0));
				//MainCam->MoveDirection.z = -20;
			}
			if (SDLEvent.key.keysym.sym == 'z') {
				//MainCam->MoveCamera(glm::vec3(0, 0.1, 0));
			}
			else if (SDLEvent.key.keysym.sym == 'x') {
				//MainCam->MoveCamera(glm::vec3(0, 0.1, 0));
			}
			break;
		case SDL_MOUSEMOTION:

			SDL_GetMouseState(&MouseX, &MouseY);
			//printf("mouse X:%d Y:%d", MouseX, MouseY);
			//MainCam->FPSCamera();
			//SDL_WarpMouseInWindow(window->WindowView, width, height);
			
			break;
		}
	}
	
}
void draw() {
	glClearColor(0.5, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Thing1->Draw();
	Thing2->Draw();
	Thing3->Draw();
	SDL_GL_SwapWindow(game->window->WindowView);
}
void loadModels() {
	Thing1 = new GameObject("Thing1", "Pyramid", GL_TRUE);
	Thing1->SetPosition(glm::vec3(-5, 0, 0));
	Thing2 = new GameObject("Thing2", "Pyramid", GL_TRUE);
	Thing3 = new GameObject("Thing3", "Pyramid", GL_TRUE);
	Thing3->SetPosition(glm::vec3(5, 0, 0));
	//MainScene->AddModel(Model("1"));
	//MainScene->GetModel("1")->LoadMesh("Pyramid");
}

int main(int argc, char *argv[]) {
	game = new NYX();
	window = game->window;
	window->setTitle("Test");
	loadModels();

	window->setUpCamera(Thing1->ShaderProgram);

	MainCam = window->MainCam;
	MainCam->SetPosition(glm::vec3(0, 0, -10));
	MainCam->SetFrustum(-0.5f, 0.5f, -0.5f, 0.5f, 1.0f, 10000);
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_TRUE);
	while (!quit) {
		update();
		draw();
	}
	delete Thing1;
	Thing1 = nullptr;
	delete Thing2;
	Thing2 = nullptr;
	delete Thing2;
	Thing2 = nullptr;
	delete game;
	game = nullptr;
	//delete MainScene;
	//MainScene = nullptr;
	return 0;
}