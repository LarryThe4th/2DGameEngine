#pragma once

#include <glm/glm.hpp>
#include <GameEngine/SpriteBatch.h>

const float AGENT_WIDTH = 80.0f;
const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;

class UFO;
class SpaceShip;

class Agent
{
public:
    Agent();
    virtual ~Agent();

    virtual void update(const std::vector<std::string>& levelData,
						std::vector<SpaceShip*>& ships,
                        std::vector<UFO*>& UFOs) = 0;

    bool collideWithLevel(const std::vector<std::string>& levelData);

    bool collideWithAgent(Agent* agent);

	// Pure virtual function, just like a abstract function.
	virtual void draw(GameEngine::SpriteBatch& _spriteBatch) = 0;
    
    // Return true if we died
    bool applyDamage(float damage);

    glm::vec2 getPosition() const { return _position; }

protected:

    void checkTilePosition(const std::vector<std::string>& levelData,
                           std::vector<glm::vec2>& collideTilePositions,
                           float x, 
                           float y);

    void collideWithTile(glm::vec2 tilePos);
    
    glm::vec2 _position;
	GameEngine::Color _color;
    float _speed;
    float _health;
};

