#pragma once
#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie();
	~Zombie();

	void InitZombie(float const speed, glm::vec2 position);

	void Update(const std::vector<std::string>& levelData,
				std::vector<Human*>& humans,
				std::vector<Zombie*>& zombies);
};

