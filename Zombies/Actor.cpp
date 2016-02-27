#include "Actor.h"
#include <GameEngine\ResourceManager.h>

Actor::Actor()
{
}


Actor::~Actor()
{
}

void Actor::AddActor(GameEngine::SpriteBatch& spriteBatch) {

	static GLuint textureID = GameEngine::ResourceManager::GetTexture("Textures/circle.png").id;

	const int ActorSpriteWidth = 32;
	const glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	// The position and size of the actor sprite.
	glm::vec4 positionAndSize(_position.x, _position.y,
		ActorSpriteWidth, ActorSpriteWidth);

	spriteBatch.AddSprite(positionAndSize, uv, textureID, 0.0f, _color);
}
