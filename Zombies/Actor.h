#pragma once
#include <glm\glm.hpp>
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\GLTexture.h>

class Actor
{
public:
	Actor();
	virtual ~Actor();

	// A pure virtual function.
	virtual void Update() = 0;

	// Add actor into the sprite batch.
	void AddActor(GameEngine::SpriteBatch& spriteBatch);

	// Getters
	glm::vec2 GetActorPosition() const { return _position; }
	

protected:
	// The position of the actor.
	glm::vec2 _position;

	// The color of the actor sprite.
	GameEngine::Color _color;

	// The movment speed of the actor.
	float _moveSpeed;
};

