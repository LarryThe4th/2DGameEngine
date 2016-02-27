#pragma once
#include "Human.h"
#include <GameEngine\InputManager.h>

class Player : public Human
{
public:
	Player();
	~Player();

	void InitPlayer(glm::vec2 position, float moveSpeed, GameEngine::InputManager* _inputManager);
	void Update();
private:
	GameEngine::InputManager* _inputManager;
};

