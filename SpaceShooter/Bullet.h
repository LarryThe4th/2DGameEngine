#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <GameEngine/SpriteBatch.h>

class UFO;
class SpaceShip;
class Agent;

const int BULLET_RADIUS = 20;

class Bullet
{
public:
    Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed);
    ~Bullet();

    // When update returns true, delete bullet
    bool update(const std::vector<std::string>& levelData);

	// Draw the bullet
    void draw(GameEngine::SpriteBatch& spriteBatch);

	// The collision detetion with agent.
    bool collideWithAgent(Agent* agent);

	// Apply damage to the agent.
    float getDamage() const { return _damage; }

private:
	// The collision detetion with world object.
    bool collideWithWorld(const std::vector<std::string>& levelData);

    glm::vec2 _position;
    glm::vec2 _direction;
    float _damage;
    float _speed;
};

