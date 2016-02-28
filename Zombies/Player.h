#pragma once
#include "Human.h"
#include <GameEngine\InputManager.h>

class Player : public Human
{
public:
	Player();
	~Player();

	void InitPlayer(glm::vec2 position, float moveSpeed, GameEngine::InputManager* _inputManager);
<<<<<<< HEAD
	void Update();
=======
	void Update(const std::vector<std::string>& levelData,
				std::vector<Human*>& humans,
				std::vector<Zombie*>& zombies);
>>>>>>> refs/remotes/origin/backUp
private:
	GameEngine::InputManager* _inputManager;
};

