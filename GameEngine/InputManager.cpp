#include "InputManager.h"
#include <iostream>

namespace GameEngine {

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::KeyPressed(SDL_Keycode keyID) {
		// The "map::operator[]" will first sreach for the value by key.
		// If the key does exist in the map then return the reference of the stored value.
		// Else if the key does not exist then it will create a new key and randomly store some value if not assigned.
		_keyMap[keyID] = true;
	}

	void InputManager::KeyReleased(SDL_Keycode keyID) {
		_keyMap[keyID] = false;
	}

	bool InputManager::IsKeyPressed(SDL_Keycode keyID) {
		auto iterator = _keyMap.find(keyID);
		if (iterator != _keyMap.end())
			return iterator->second;
		else
			return false;
	}
}
