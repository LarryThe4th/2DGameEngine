#include "Bullet.h"
#include <GameEngine/ResourceManager.h>

#include "Agent.h"
#include "SpaceShip.h"
#include "UFO.h"
#include "Level.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float damage, float speed) :
    _position(position),
    _direction(direction),
    _damage(damage),
    _speed(speed) {
}


Bullet::~Bullet() {
}


bool Bullet::update(const std::vector<std::string>& levelData) {
    _position += _direction * _speed;
    return collideWithWorld(levelData);
}

void Bullet::draw(GameEngine::SpriteBatch& spriteBatch) {
    //glm::vec4 destRect(_position.x + BULLET_RADIUS,
    //                   _position.y + BULLET_RADIUS,
    //                   BULLET_RADIUS * 2,
    //                   BULLET_RADIUS * 2);

	glm::vec4 destRect(_position.x,
	                   _position.y,
	                   BULLET_RADIUS * 2,
	                   BULLET_RADIUS * 2);


    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	GameEngine::Color color;
    color.red = 255;
    color.green = 255;
    color.blue = 255;
    color.alpha = 255;

    spriteBatch.AddSprite(destRect, uvRect, GameEngine::ResourceManager::GetTexture("Textures/Bullet.png").id, 0.0f, color);
}

bool Bullet::collideWithAgent(Agent* agent) {
    const float MIN_DISTANCE = AGENT_RADIUS + BULLET_RADIUS;

    glm::vec2 centerPosA = _position;
    glm::vec2 centerPosB = agent->getPosition() + glm::vec2(AGENT_RADIUS);

    glm::vec2 distVec = centerPosA - centerPosB;

    float distance = glm::length(distVec);

    float collisionDepth = MIN_DISTANCE - distance;
    if (collisionDepth > 0) { 
        return true;
    }
    return false;
}

bool Bullet::collideWithWorld(const std::vector<std::string>& levelData) {
    glm::ivec2 gridPosition;
    gridPosition.x = (int)floor(_position.x / (float)TILE_WIDTH);
    gridPosition.y = (int)floor(_position.y / (float)TILE_WIDTH);

    // If we are outside the world, just return
    if (gridPosition.x < 0 || (int)gridPosition.x >= levelData[0].size() ||
        gridPosition.y < 0 || (int)gridPosition.y >= levelData.size()) {
        return true;
    }

    return (levelData[gridPosition.y][gridPosition.x] != '.');
}