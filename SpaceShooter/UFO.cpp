#include "UFO.h"
#include <GameEngine\ResourceManager.h>
#include "SpaceShip.h"

UFO::UFO()
{
}

UFO::~UFO()
{
}

void UFO::init(float speed, glm::vec2 pos) {
    _speed = speed;
    _position = pos;
    _health = 150;
    // Set Green Color
    _color.red = 225;
    _color.green = 225;
    _color.blue = 225;
    _color.alpha = 255;
}

void UFO::update(const std::vector<std::string>& levelData,
                    std::vector<SpaceShip*>& ships,
                    std::vector<UFO*>& UFOs) {

    // Find the closest ship
	SpaceShip* closestShip = getNearestShip(ships);

    // If we found a ship, move towards him
    if (closestShip != nullptr) {
        // Get the direction vector twoards the player
        glm::vec2 direction = glm::normalize(closestShip->getPosition() - _position);
        _position += direction * _speed;
    }

    // Do collision
    collideWithLevel(levelData);
}

void UFO::draw(GameEngine::SpriteBatch& _spriteBatch) {
	static int UFOtextureID = GameEngine::ResourceManager::GetTexture("Textures/UFO.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	_spriteBatch.AddSprite(destRect, uvRect, UFOtextureID, 0.0f, _color);
}

SpaceShip* UFO::getNearestShip(std::vector<SpaceShip*>& ships) {
	SpaceShip* closestShip = nullptr;
    float smallestDistance = 9999999.0f;

    for (size_t i = 0; i < ships.size(); i++) {
        // Get the direction vector
        glm::vec2 distVec = ships[i]->getPosition() - _position;
        // Get distance
        float distance = glm::length(distVec);

        // If this person is closer than the closest person, this is the new closest
        if (distance < smallestDistance) {
            smallestDistance = distance;
			closestShip = ships[i];
        }
    }
    
    return closestShip;
}