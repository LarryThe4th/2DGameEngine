#pragma once
#include "Human.h"
#include <GameEngine\InputManager.h>

class Player : public Human
{
public:
	Player();
	~Player();

	void InitPlayer(glm::vec2 position, float moveSpeed, GameEngine::InputManager* _inputManager);
	void Update(const std::vector<std::string>& levelData,
				std::vector<Human*>& humans,
				std::vector<Zombie*>& zombies);
private:
	GameEngine::InputManager* _inputManager;
};

