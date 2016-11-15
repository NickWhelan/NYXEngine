#include "pch.h"
#include "GameEngine.h"

GameEngine::GameEngine()
{
	Renderer = new OpenGLRenderer();
	Window = new WindowView();
}
/*controller update isnt being called idk why*/
void GameEngine::Update() {
	while (SDL_PollEvent(&SDLEvent))
	{
		//std::cout << "SDLEvent.type" << SDLEvent.type << "\n";
		switch (SDLEvent.type) {
		case SDL_EventType::SDL_QUIT:
			quit = true;
			return;
		case SDL_EventType::SDL_CONTROLLERDEVICEADDED:
			Controllers[SDLEvent.cdevice.which] = new Controller();
			Controllers[SDLEvent.cdevice.which]->AddController(SDLEvent.cdevice.which);
			printf("Added %f", SDLEvent.cdevice.which);
			return;
		case SDL_EventType::SDL_CONTROLLERDEVICEREMOVED:
			Controllers[SDLEvent.cdevice.which]->RemoveController(SDLEvent.cdevice.which);
			Controllers[SDLEvent.cdevice.which] = NULL;
			printf("Removed %f", SDLEvent.cdevice.which);
			return;
			/*
		case SDL_EventType::SDL_CONTROLLERBUTTONDOWN:
			return;
		case SDL_EventType::SDL_CONTROLLERBUTTONUP:
			return;
		case SDL_EventType::SDL_CONTROLLERAXISMOTION:
			return;
							*/
		case SDL_EventType::SDL_KEYDOWN:
			if (SDLEvent.key.keysym.sym == SDLK_w) {
				Renderer->CameraOne->CamDist += 1;
				printf("%f\n", Renderer->CameraOne->CamDist);
			}
			else if (SDLEvent.key.keysym.sym == SDLK_s) {
				Renderer->CameraOne->CamDist -= 1;
				printf("%f\n", Renderer->CameraOne->CamDist);
			}
			return;

		case SDL_EventType::SDL_KEYUP:
			if (SDLEvent.key.keysym.sym == SDLK_q)
				quit = true;
			//printf("quit");
			return;
		}
	}
}
void GameEngine::Draw() {
	Renderer->PreRender();
	Renderer->PostRender();
}
void GameEngine::GameLoop() {
	Renderer->renderPrimitive(AbstractRenderer::PRIMITIVETYPE::TRIANGLE);
	// Game loop
	while (!quit)
	{
		Update();
		Draw();
		// Update window with OpenGL rendering
		SDL_GL_SwapWindow(Window->GetWindow());
	}
	//Quit SDL subsystems
	Quit();
}

void GameEngine::Quit() {
	Window->DestroyWindow();
	delete Window;
	Window = nullptr;
	SDL_Quit();
}
GameEngine::~GameEngine() {
	Quit();
}

