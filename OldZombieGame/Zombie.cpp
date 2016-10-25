#include "Zombie.h"

Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::InitZombie(float const speed, glm::vec2 position) {
	_moveSpeed = speed;
	_position = position;

	_color.red = 0;
	_color.green = 160;
	_color.blue = 0;
	_color.alpha = 255;
}

void Zombie::Update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies) {
}

