#pragma once

#include "Agent.h"

class SpaceShip : public Agent
{
public:
	SpaceShip();
    virtual ~SpaceShip();

    void init(float speed, glm::vec2 pos);

    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<SpaceShip*>& ships,
                        std::vector<UFO*>& UFOs);

	virtual void draw(GameEngine::SpriteBatch& _spriteBatch);


private:
    glm::vec2 _direction;
    int _frames;
};

