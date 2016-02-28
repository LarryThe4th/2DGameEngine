#pragma once
#include <glm\glm.hpp>
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\GLTexture.h>

class Human;
class Zombie;

class Actor
{
public:
	Actor();
	virtual ~Actor();

	// A pure virtual function.
	virtual void Update(const std::vector<std::string>& levelData,
						std::vector<Human*>& humans,
						std::vector<Zombie*>& zombies) = 0;

	void CollideWithLevel(const std::vector<std::string>& levelData);

	// Add actor into the sprite batch.
	void AddActor(GameEngine::SpriteBatch& spriteBatch);

	// Getters
	glm::vec2 GetActorPosition() const { return _position; }
protected:
	void CheckTilePosition(const std::vector<std::string>& levelData,
						   std::vector<glm::vec2>& collideTilePositions,
						   float cornerPositionX, float cornerPositionY);

	void CollideWithTile(glm::vec2 tilePosition);

	// The position of the actor.
	glm::vec2 _position;

	// The size of the actor sprite
	const float _ActorSpriteWidth = 32;

	// The color of the actor sprite.
	GameEngine::Color _color;

	// The movment speed of the actor.
	float _moveSpeed;
};

