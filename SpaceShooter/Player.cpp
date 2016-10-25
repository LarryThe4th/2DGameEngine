#include "Player.h"
#include <SDL/SDL.h>

#include "Gun.h"

Player::Player() :
    _currentGunIndex(-1) {
    // Empty
}

Player::~Player() {
    // Empty
}

void Player::init(float speed, glm::vec2 pos, GameEngine::InputManager* inputManager, GameEngine::Camera2D* camera, std::vector<Bullet>* bullets) {
    _speed = speed;
    _position = pos;
    _inputManager = inputManager;
    _bullets = bullets;
    _camera = camera;
    _color.red = 225;
    _color.green = 225;
    _color.blue = 225;
    _color.alpha = 255;
    _health = 150;
}

void Player::addGun(Gun* gun) {
    // Add the gun to his inventory
    _guns.push_back(gun);

    // If no gun equipped, equip gun.
    if (_currentGunIndex == -1) {
        _currentGunIndex = 0;
    }
}

void Player::draw(GameEngine::SpriteBatch& _spriteBatch) {
	static int platTextureID = GameEngine::ResourceManager::GetTexture("Textures/Player.png").id;

	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	glm::vec4 destRect;
	destRect.x = _position.x;
	destRect.y = _position.y;
	destRect.z = AGENT_WIDTH;
	destRect.w = AGENT_WIDTH;

	_spriteBatch.AddSprite(destRect, uvRect, platTextureID, 0.0f, _color);
}

void Player::update(const std::vector<std::string>& levelData,
                    std::vector<SpaceShip*>& ships,
                    std::vector<UFO*>& UFOs) {

	// Move the character using simple wsad.
    if (_inputManager->IsKeyPressed(SDLK_w)) {
        _position.y += _speed;
    } else if (_inputManager->IsKeyPressed(SDLK_s)) {
        _position.y -= _speed;
    }
    if (_inputManager->IsKeyPressed(SDLK_a)) {
        _position.x -= _speed;
    } else if (_inputManager->IsKeyPressed(SDLK_d)) {
        _position.x += _speed;
    }

	// Selected defferent weapon.
    if (_inputManager->IsKeyPressed(SDLK_1) && _guns.size() >= 0) {
        _currentGunIndex = 0;
	}
	//else if (_inputManager->IsKeyPressed(SDLK_2) && _guns.size() >= 1) {
	//	_currentGunIndex = 1;
	//}

	// If the player character equiped a gun in slot.
    if (_currentGunIndex != -1) {
		// Get the mouse coords and convert in to game word coordinates.
        glm::vec2 mouseCoords = _inputManager->GetMouseScreenCoordinate();
        mouseCoords = _camera->GetWorldFormScreen(mouseCoords);

		// Get the position where the bullet start to fly.
        glm::vec2 centerPosition = _position + glm::vec2(AGENT_RADIUS);
		// glm::vec2 centerPosition = _position;

		// Get the vector from fire location to the mouse point as the bullet travel direction.
        glm::vec2 direction = glm::normalize(mouseCoords - centerPosition);

		// Update the gun.
        _guns[_currentGunIndex]->update(_inputManager->IsKeyPressed(SDL_BUTTON_LEFT),
                                        centerPosition,
                                        direction,
                                        *_bullets);
    }

    collideWithLevel(levelData);
}
