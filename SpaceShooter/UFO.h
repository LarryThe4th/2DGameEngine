#pragma once

#include "Agent.h"

class UFO : public Agent
{
public:
	UFO();
    ~UFO();

    void init(float speed, glm::vec2 pos);

    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<SpaceShip*>& ships,
                        std::vector<UFO*>& UFOs);

	void draw(GameEngine::SpriteBatch& _spriteBatch) override;
private:

	SpaceShip* getNearestShip(std::vector<SpaceShip*>& ships);
};

