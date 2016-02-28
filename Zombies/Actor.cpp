#include "Actor.h"
#include <GameEngine\ResourceManager.h>
<<<<<<< HEAD
=======
#include <iostream>
#include "Level.h"
#include <algorithm>
>>>>>>> refs/remotes/origin/backUp

Actor::Actor()
{
}


Actor::~Actor()
{
}

void Actor::AddActor(GameEngine::SpriteBatch& spriteBatch) {

	static GLuint textureID = GameEngine::ResourceManager::GetTexture("Textures/circle.png").id;
<<<<<<< HEAD

	const int ActorSpriteWidth = 32;
=======
>>>>>>> refs/remotes/origin/backUp
	const glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	// The position and size of the actor sprite.
	glm::vec4 positionAndSize(_position.x, _position.y,
<<<<<<< HEAD
		ActorSpriteWidth, ActorSpriteWidth);

	spriteBatch.AddSprite(positionAndSize, uv, textureID, 0.0f, _color);
}
=======
		_ActorSpriteWidth, _ActorSpriteWidth);

	spriteBatch.AddSprite(positionAndSize, uv, textureID, 0.0f, _color);
}

void Actor::CollideWithLevel(const std::vector<std::string>& levelData) {
	std::vector<glm::vec2> collideTilePositions;
	// The first corner.
	CheckTilePosition(levelData, collideTilePositions, _position.x, _position.y);

	// The sceond corner.
	CheckTilePosition(levelData, collideTilePositions, _position.x + _ActorSpriteWidth, _position.y);

	// The third corner.
	CheckTilePosition(levelData, collideTilePositions, _position.x , _position.y + _ActorSpriteWidth);

	// The fourth corner.
	CheckTilePosition(levelData, collideTilePositions, _position.x + _ActorSpriteWidth, _position.y + _ActorSpriteWidth);
	
	for (size_t i = 0; i < collideTilePositions.size(); i++)
	{
		CollideWithTile(collideTilePositions[i]);
	}
}

void Actor::CheckTilePosition(const std::vector<std::string>& levelData, 
							std::vector<glm::vec2>& collideTilePositions, 
							float cornerPositionX, float cornerPositionY) {
	// Check the for corners.
	glm::vec2 cornerPosition = glm::vec2(floor(cornerPositionX / _ActorSpriteWidth),
		floor(cornerPositionY / _ActorSpriteWidth));

	if (levelData[cornerPosition.y][cornerPosition.x] != '.') {
		collideTilePositions.push_back(cornerPosition * _ActorSpriteWidth + glm::vec2(_ActorSpriteWidth / 2.0f, _ActorSpriteWidth / 2.0f));
	}
}

// Axis-Aligned Bounding Box collision.
void Actor::CollideWithTile(glm::vec2 tilePosition) {
	const float ActorRadius = _ActorSpriteWidth / 2.0f;
	const float TileRadius = _ActorSpriteWidth / 2.0f;
	const float MinimunDistance = ActorRadius + TileRadius;

	glm::vec2 playerCenterPosition = _position + glm::vec2(ActorRadius);
	glm::vec2 distance = playerCenterPosition - tilePosition;

	float xDepth = MinimunDistance - abs(distance.x);
	float yDepth = MinimunDistance - abs(distance.y);

	// If this is true, we are colliding.
	if (xDepth > 0 || yDepth > 0) {
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			if (distance.x < 0) {
				_position.x -= xDepth;
			}
			else
			{
				_position.x += xDepth;
			}
		}
		else
		{
			if (distance.y < 0) {
				_position.y -= yDepth;
			}
			else
			{
				_position.y += yDepth;
			}
		}
	}
}
>>>>>>> refs/remotes/origin/backUp
