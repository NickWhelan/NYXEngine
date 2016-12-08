#include "SDL\Include\SDL.h"
#include "glm\glm\gtc\matrix_transform.hpp"
#include "NYX.h"
#include "Model.h"
bool quit = false;
SDL_Event SDLEvent;
NYX* game;
Window * window;
Camera* MainCam;
Model* Thing;
int MouseX, MouseY;
const float  MouseSensitivity = 0.001;
float Delta = 0.66;
/*
float x = glm::cos(cameraAngleX);
float z = glm::sin(cameraAngleX);
float YA = glm::cos(cameraAngleY);
float y = glm::sin(cameraAngleY);
//Vector3 position = window->GetCamera()->GetPosition();
float vX = x * YA;
float vZ = z * YA;
if(Input::LockPointer)
	window->GetCamera()->Look(Vector3(x * YA, -y, z * YA), Vector3(0, 1.0f, 0));
Vector3 direction = glm::normalize(window->GetCamera()->GetDirection());
direction.y = 0;
Vector3 forward = direction * MoveDirection.x;
Vector3 sideways = glm::cross(direction, Vector3(0, 1, 0)) * MoveDirection.z;
window->GetCamera()->Move((forward + sideways) * 150.0f * Delta);
window->GetCamera()->Move(Vector3(0, MoveDirection.y * 75.0f * Delta, 0));
*/
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
			/*
			SDL_GetMouseState(&MouseX, &MouseY);
			//printf("mouse X:%d Y:%d", MouseX, MouseY);
			float width = window->WIDTH / 2;
			float height = window->HEIGHT / 2;
			float aspect = width / height;
			MainCam->Rotation.x += (MouseX - width) * MouseSensitivity;
			MainCam->Rotation.y += (MouseY - height) * MouseSensitivity*aspect;
			//MainCam->FPSCamera();
			SDL_WarpMouseInWindow(window->WindowView, width, height);
			*/
			break;
		}
	}
	
}
void draw() {
	glClearColor(0.5, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Thing->Draw();
	//glFlush();
	SDL_GL_SwapWindow(game->window->WindowView);
}

int main(int argc, char *argv[]) {
	game = new NYX();
	Thing = new Model();
	window = game->window;
	window->setTitle("Test");
	Thing->LoadMesh("Pyramid");
	window->setUpCamera(Thing->Render->Program);
	MainCam = window->MainCam;
	MainCam->SetPosition(glm::vec3(0, 0, -10));
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_TRUE);
	while (!quit) {
		update();
		draw();
	}
	delete game;
	game = nullptr;
	delete Thing;
	Thing= nullptr;
	return 0;
}