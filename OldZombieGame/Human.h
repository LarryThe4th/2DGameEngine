#pragma once
#include "Actor.h"

class Human : public Actor
{
public:
	Human();
	virtual ~Human();

	void InitHuman(glm::vec2 position, float moveSpeed);

	virtual void Update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies);

private:
	glm::vec2 _direction;
	int _frame;
};

