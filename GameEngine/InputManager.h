#pragma once
#include <SDL\SDL.h>
#include <unordered_map>
#include <glm\glm.hpp>

namespace GameEngine {

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void KeyPressed(SDL_Keycode keyID);
		void KeyReleased(SDL_Keycode keyID);
		bool IsKeyPressed(SDL_Keycode keyID);

		void SetMouseScreenCoordinate(float x, float y);

		// A constant function.
		// Meaning a function that will not alter any member variables of the class it belongs to.
		// Recommended to use for getters.
		glm::vec2 GetMouseScreenCoordinate() const { return _mouseScreenCoordinate; }

	private:
		std::unordered_map<SDL_Keycode, bool> _keyMap;
		glm::vec2 _mouseScreenCoordinate;
	};
}
