#include <iostream>
#include "Window.h"
#include "ErrorMessage.h"

namespace GameEngine {

	Window::Window() :
		_window(nullptr)
	{
	}


	Window::~Window()
	{
	}

	int Window::CreateWindow(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
		Uint32 flags = SDL_WINDOW_OPENGL;
		if (currentFlags & INVISIBLE) {
			flags |= SDL_WINDOW_HIDDEN;
		}
		if (currentFlags & FULLSCREEN) {
			//flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		if (currentFlags & BORDERLESS) {
			flags |= SDL_WINDOW_BORDERLESS;
		}
		if (currentFlags & WINDOWMODE) {
			flags |= SDL_WINDOW_OPENGL;
		}

		// Create an SDL window.
		_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (_window == nullptr) {
			FatalError("Failed to created SDL window.");
		}

		// Set up our Opengl context.
		SDL_GLContext sdlConetxt = SDL_GL_CreateContext(_window);
		if (sdlConetxt == nullptr) {
			FatalError("Failed to created SDL_GL context.");
		}

		// Set up glew (optional but recommended).
		GLenum error = glewInit();
		if (error != GLEW_OK) {
			FatalError("Failed to initialize glew.");
		}

		// Check the opengl version.
		std::cout << "----- OpenGL version : " << glGetString(GL_VERSION) << " -----\n";

		// Set the background color.
		glClearColor(0.6f, 0.6f, 0.6f, 1.0f);

		// Set to 1 to enable VSYNC or 0 to disbale VSYNC.
		SDL_GL_SetSwapInterval(1);

		return 0;
	}

	void Window::SwapBuffer() {
		SDL_GL_SwapWindow(_window);
	}
}