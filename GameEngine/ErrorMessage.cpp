#include <iostream>
#include <SDL\SDL.h>
#include <cstdlib>

#include "ErrorMessage.h"

namespace GameEngine {

	void GameEngine::FatalError(std::string errorMessage) {
		std::cout << errorMessage << std::endl;
		std::cout << "Enter any key to quit." << std::endl;

		int tmp;
		std::cin >> tmp;

		// SDL_Quit() will only shutdown SDL itself but not the program.
		SDL_Quit();
		// So exit(1) is needed after shutdown SDL.
		exit(1);
	}
}