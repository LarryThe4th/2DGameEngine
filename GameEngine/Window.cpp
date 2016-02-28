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
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

		// Set to 1 to enable VSYNC or 0 to disbale VSYNC.
		SDL_GL_SetSwapInterval(1);

		// Enable alpha blend, much easier than i think.
		glEnable(GL_BLEND);

		// Define how the opengl handles alpha channel.
		// --------------------------------------------------------------
		// So this is how i understand it:
		// 1. The first argument specifies which value you want multiply by the source image's color, it can be red, greem, blue and alpha.
		//		Set the first argument as "GL_SRC_ALPHA" will take the scorce image's alpha channel and multiply with the color.
		// 2. The sceond argument specifies how much you want to blend with the existed color.
		//		For example the back ground color is RED, and you have a other image on the top of the back ground.
		//		If the alpha of the source image is 1, 1 minus 1 ("GL_ONE_MINUS_SRC_ALPHA") equals 0. 
		//		0 multiply by the existed color RED is 0 so no transparency.
		//		If the alpha of the source image is 0, 1 minus 0 equals 1.
		//		1 multiply by the existed color RED equals to the origin color that is RED, so completely see through.
		// --------------------------------------------------------------
		// One more example:
		//		DestinationColor = (1.0f, 0.0f, 0.0f, 0.0f) // Red
		//		SourceColor = (0.0f, 0.0f, 1.0f, 0.6f) // Blue, source alpha= 0.6f
		//		One Minus Source Alpha = 1.0 – 0.6 = 0.4
		//	Resolving final color:
		//		// Blended color = (source color * source alpha) + (destination color * one_minus_source_alpha)
		//		BlendedColor = (SourceColor * 0.6) + (DestinationColor * 0.4)
		//		BlendedColor = (0.4f, 0.0f, 0.6f)
		// --------------------------------------------------------------
		// More information see: https://www.opengl.org/sdk/docs/man/html/glBlendFunc.xhtml
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::SwapBuffer() {
		SDL_GL_SwapWindow(_window);
	}
}