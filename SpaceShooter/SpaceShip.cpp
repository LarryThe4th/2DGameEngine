#include "SpaceShip.h"
#include <ctime>
#include <random>
#include <glm/gtx/rotate_vector.hpp>
#include <GameEngine\ResourceManager.h>

SpaceShip::SpaceShip() :
    _frames(0)
{
}


SpaceShip::~SpaceShip()
{
}

void SpaceShip::init(float speed, glm::vec2 pos) {

    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randDir(-1.0f, 1.0f);

    _health = 20;

    _color.red = 225;
    _color.green = 225;
    _color.blue = 225;
    _color.alpha = 255;

    _speed = speed;
    _position = pos;
    // Get random direction
    _direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
    // Make sure direction isn't zero
    if (_direction.length() == 0) _direction = glm::vec2(1.0f, 0.0f);

    _direction = glm::normalize(_direction);
}

void SpaceShip::draw(GameEngine::SpriteBatch& _spriteBatch) {
	static int shipTextureID = GameEngine::ResourceManager::GetTexture("Textures/Ship.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	_spriteBatch.AddSprite(destRect, uvRect, shipTextureID, 0.0f, _color);
}

void SpaceShip::update(const std::vector<std::string>& levelData,
                   std::vector<SpaceShip*>& ships,
                   std::vector<UFO*>& UFOs) {

    static std::mt19937 randomEngine(time(nullptr));
    static std::uniform_real_distribution<float> randRotate(-40.0f, 40.0f);

    _position += _direction * _speed;

    // Randomly change direction every 20 frames
    if (_frames == 20) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
        _frames = 0;
    } else {
        _frames++;
    }

    if (collideWithLevel(levelData)) {
        _direction = glm::rotate(_direction, randRotate(randomEngine));
    }
}