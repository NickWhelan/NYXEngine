#include "pch.h"
#include "WindowView.h"


WindowView::WindowView()
{
}

void WindowView::WindowSetup(char Name[],float Width, float Height) {

	//Use OpenGL 3.1 core
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// Initialize video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		// Display error message
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	else
	{
		// Create window
		window = SDL_CreateWindow(Name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == NULL)
			// Display error message
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		else
		{
			// Create OpenGL context
			SDLRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			glContext = SDL_GL_CreateContext(window);
			if (glContext == NULL)
				// Display error message
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
			else {
				// Initialize glew
				glewInit();
				
				//glEnable(GL_DEPTH_TEST);
				//glDepthFunc(GL_LESS);
			}
		}
	}
	
}
SDL_Renderer* WindowView::GetRenderer() const {
	return SDLRenderer;
}

SDL_Window* WindowView::GetWindow() {
	return window;
}

SDL_GLContext WindowView::GetContext() {
	return glContext;
}
void WindowView::ToggleFullScreen() {
	bIsFullScreen = !bIsFullScreen;
	SDL_SetWindowFullscreen(window, (bIsFullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN));
}
void WindowView::DestroyWindow() {
	//Destroy window
	SDL_DestroyWindow(window);
	delete window;
	window = NULL;
}
WindowView::~WindowView()
{
}
