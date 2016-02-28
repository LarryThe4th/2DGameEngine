#include "Player.h"
#include <SDL\SDL.h>

Player::Player()
{
}


Player::~Player()
{
}

void Player::InitPlayer(glm::vec2 position, float moveSpeed, GameEngine::InputManager* inputManager) {
	_position = position;
	_moveSpeed = moveSpeed;

	_inputManager = inputManager;

	_color.red = 0;
	_color.green = 0;
	_color.blue = 185;
	_color.alpha = 225;
}

<<<<<<< HEAD
void Player::Update() {
=======
void Player::Update(const std::vector<std::string>& levelData,
					std::vector<Human*>& humans,
					std::vector<Zombie*>& zombies) {
>>>>>>> refs/remotes/origin/backUp
	if (_inputManager->IsKeyPressed(SDLK_w)) {
		_position.y += _moveSpeed;
	}

	if (_inputManager->IsKeyPressed(SDLK_s)) {
		_position.y -= _moveSpeed;
	}

	if (_inputManager->IsKeyPressed(SDLK_a)) {
		_position.x -= _moveSpeed;
	}

	if (_inputManager->IsKeyPressed(SDLK_d)) {
		_position.x += _moveSpeed;
	}
<<<<<<< HEAD
=======

	CollideWithLevel(levelData);
>>>>>>> refs/remotes/origin/backUp
}
