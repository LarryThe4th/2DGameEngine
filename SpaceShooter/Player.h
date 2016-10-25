#pragma once

#include "SpaceShip.h"
#include <GameEngine/InputManager.h>
#include <GameEngine/Camera2D.h>
#include <GameEngine/ResourceManager.h>
#include "Bullet.h"

class Gun;

class Player : public SpaceShip
{
public:
    Player();
    ~Player();

    void init(float speed, glm::vec2 pos, GameEngine::InputManager* inputManager, GameEngine::Camera2D* camera, std::vector<Bullet>* bullets);

    void addGun(Gun* gun);

    void update(const std::vector<std::string>& levelData,
                std::vector<SpaceShip*>& ships,
                std::vector<UFO*>& UFOs) override;

	void draw(GameEngine::SpriteBatch& _spriteBatch) override;

private:
	GameEngine::InputManager* _inputManager;

    std::vector<Gun*> _guns;
    int _currentGunIndex;

	GameEngine::Camera2D* _camera;
    std::vector<Bullet>* _bullets;

};

