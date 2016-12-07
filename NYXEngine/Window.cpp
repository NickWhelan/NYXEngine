#include "Window.h"

Window* Window::Instance = 0;
Window::Window()
{
}

void Window::WindowSetUp(float _Width, float _Height) {
	WIDTH = _Width;
	HEIGHT = _Height;
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
		WindowView = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (WindowView == NULL)
			// Display error message
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		else
		{
			// Create OpenGL context
			SDLWindowRenderer = SDL_CreateRenderer(WindowView, -1, SDL_RENDERER_ACCELERATED);
			WindowGlContext = SDL_GL_CreateContext(WindowView);
			if (WindowGlContext == NULL)
				// Display error message
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
			else {
				// Initialize glew
				glewInit();

				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);
			}
		}
	}
}
void Window::setUpCamera(GLuint Program) {
	//MainCam = new Camera(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), Program);
	//MainCam->Persepective(45, 1, 1, 20);
}
void Window::setTitle(std::string Title) {
	SDL_SetWindowTitle(WindowView, Title.c_str());
}
Window* Window::GetInstance() {
	if (Instance == 0) {
		Instance = new Window();
	}
	return Instance;
}
void Window::setSize(float _Width, float _Height) {
	WIDTH = _Width;
	HEIGHT = _Height;
	SDL_SetWindowSize(WindowView, _Width, _Height);
	SDL_SetWindowPosition(WindowView,SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
void Window::setFullScreen() {
	if (SDL_WINDOW_FULLSCREEN){
		SDL_SetWindowFullscreen(WindowView, true);
	}
	else {
		SDL_SetWindowFullscreen(WindowView, false);
	}
}

Window::~Window()
{
	delete Instance;
	//delete MainCam;
	Instance = nullptr;
	//MainCam = nullptr;
}
