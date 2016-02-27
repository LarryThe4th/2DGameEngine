#pragma once
#include "Actor.h"

class Human : public Actor
{
public:
	Human();
	virtual ~Human();

	virtual void Update();
};

