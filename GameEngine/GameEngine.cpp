#include <SDL\SDL.h>
#include <GL\glew.h>
#include "GameEngine.h"

namespace GameEngine {

	int InitEngine() {
		// Initialize SDL.
		SDL_Init(SDL_INIT_EVERYTHING);

		// Enbale double buffer function.
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		return 0;
	}
}