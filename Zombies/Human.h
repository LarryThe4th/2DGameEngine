#pragma once
#include "Actor.h"

class Human : public Actor
{
public:
	Human();
	virtual ~Human();

<<<<<<< HEAD
	virtual void Update();
=======
	virtual void Update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies);
>>>>>>> refs/remotes/origin/backUp
};

