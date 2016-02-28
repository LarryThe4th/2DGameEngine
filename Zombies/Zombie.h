#pragma once
#include "Actor.h"

class Zombie : public Actor
{
public:
	Zombie();
	~Zombie();

	void Update(const std::vector<std::string>& levelData,
				std::vector<Human*>& humans,
				std::vector<Zombie*>& zombies);
};

