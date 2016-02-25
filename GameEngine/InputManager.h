#pragma once
#include <SDL\SDL.h>
#include <unordered_map>

namespace GameEngine {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void KeyPressed(SDL_Keycode keyID);
		void KeyReleased(SDL_Keycode keyID);

		bool IsKeyPressed(SDL_Keycode keyID);
	private:
		std::unordered_map<SDL_Keycode, bool> _keyMap;
	};
}
