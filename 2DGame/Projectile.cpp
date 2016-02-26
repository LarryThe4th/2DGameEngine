#include "Projectile.h"
#include <GameEngine\ResourceManager.h>
#include <iostream>


Projectile::Projectile(float speed, glm::vec2 position, glm::vec2 direction, int lifeTime) :
	_lifeTime(0),
	_movingSpeed(0.0f),
	_position(0.0f, 0.0f),
	_direction(0.0f, 0.0f)
{
	InitProjectile(speed, position, direction, lifeTime);
}


Projectile::~Projectile()
{
}

// Initialize this projectile.
void Projectile::InitProjectile(float speed, glm::vec2 position, glm::vec2 direction, int lifeTime)
{
	_lifeTime = lifeTime;
	_movingSpeed = speed;
	_position = position;
	_direction = direction;
}

void Projectile::AddProjectile(GameEngine::SpriteBatch& spriteBatch) {
	glm::vec4 positionAndSize(_position.x, _position.y, 30.0f, 30.0f);
	static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/Fallout.png");
	static GameEngine::Color color;
	color.red = 225;
	color.green = 225;
	color.blue = 225;
	color.alpha = 225;

	spriteBatch.AddSprite(positionAndSize, uv, texture.id, 0.0f, color);
}

void Projectile::UpdateProjectile() {
	_position += ( _direction * _movingSpeed );
	_lifeTime--;
}

bool Projectile::IsLifeTimePassed() {
	if (_lifeTime == 0)
		return true;
	else
		return false;
}

