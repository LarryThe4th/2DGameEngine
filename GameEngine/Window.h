#pragma once
#include<SDL\SDL.h>
#include<GL\glew.h>
#include<string>

namespace GameEngine {
	// The options of window creation.
	enum WindowFlags {
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2,
		BORDERLESS = 0x4,
		WINDOWMODE = 0x8,
	};

	class Window
	{
	public:
		Window();
		~Window();

		// Create a new window.
		int CreateWindow(std::string windowName, int windowWidth, int windowHeight, unsigned int currentFlags);
		// Swap buffer.
		void SwapBuffer();

		// Get screen size.
		int GetScreenWidth() { _windowWidth; }
		int GetScreenHeight() { _windowHeight; }

	private:
		SDL_Window* _window;

		// Display size.
		int _windowWidth;
		int _windowHeight;
	};
}