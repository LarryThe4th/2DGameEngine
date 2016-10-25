#include "Human.h"
#include <ctime>
#include <random>
#include <GameEngine/ErrorMessage.h>
#include <glm\gtx\rotate_vector.hpp>

Human::Human() : _frame(0)
{
}


Human::~Human()
{
}

void Human::InitHuman(glm::vec2 position, float moveSpeed) {
	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randomDirection(-1.0f, 1.0f);

	_color.red = 255;
	_color.green = 0;
	_color.blue = 200;
	_color.alpha = 255;

	_position = position;
	_moveSpeed = moveSpeed;
	_direction = glm::vec2(randomDirection(randomEngine), randomDirection(randomEngine));
	if (_direction.length() == 0) _direction = glm::vec2(1.0f, 0.0f);

	_direction = glm::normalize(_direction);
}

void Human::Update(const std::vector<std::string>& levelData,
					std::vector<Human*>& humans,
					std::vector<Zombie*>& zombies) {
	_position += _direction * _moveSpeed;

	static std::mt19937 randomEngine(time(nullptr));
	static std::uniform_real_distribution<float> randomRoatation(-10.0f, 10.0f);

	// Randomly change direction every 20 frame.
	if (_frame >= 120) {
		_direction = glm::rotate(_direction, randomRoatation(randomEngine));
		_frame = 0;
	}
	else
	{
		_frame++;
	}

	if (CollideWithLevel(levelData)) {
		_direction = glm::rotate(_direction, randomRoatation(randomEngine));
	}
}
