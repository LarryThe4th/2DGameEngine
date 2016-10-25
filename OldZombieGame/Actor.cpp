#include "Actor.h"
#include <GameEngine\ResourceManager.h>
#include <iostream>
#include "Level.h"
#include <algorithm>

Actor::Actor()
{
}


Actor::~Actor()
{
}

void Actor::AddActor(GameEngine::SpriteBatch& spriteBatch) {

	static GLuint textureID = GameEngine::ResourceManager::GetTexture("Textures/circle.png").id;
	const glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	// The position and size of the actor sprite.
	glm::vec4 positionAndSize(_position.x, _position.y,
		ActorWidth, ActorWidth);

	spriteBatch.AddSprite(positionAndSize, uv, textureID, 0.0f, _color);
}

bool Actor::CollideWithLevel(const std::vector<std::string>& levelData) {
	std::vector<glm::vec2> collideTilePositions;
	// The first corner.
	CheckTilePosition(levelData, collideTilePositions, _position.x, _position.y);

	// The sceond corner.
	CheckTilePosition(levelData, collideTilePositions, _position.x + ActorWidth, _position.y);

	// The third corner.
	CheckTilePosition(levelData, collideTilePositions, _position.x , _position.y + ActorWidth);

	// The fourth corner.
	CheckTilePosition(levelData, collideTilePositions, _position.x + ActorWidth, _position.y + ActorWidth);
	
	if (collideTilePositions.size() == 0) { return false; }

	for (size_t i = 0; i < collideTilePositions.size(); i++)
	{
		CollideWithTile(collideTilePositions[i]);
	}

	return true;
}

bool Actor::CollideWithActors(Actor* actor) {

	const float MinimunDistance = ActorRadius * 2.0f;
	glm::vec2 centerPositionA = _position + glm::vec2(ActorRadius);
	glm::vec2 centerPositionB = actor->GetActorPosition() + glm::vec2(ActorRadius);

	glm::vec2 distance = centerPositionA - centerPositionB;

	float collisionDistance = glm::length(distance);
	if ((MinimunDistance - collisionDistance) > 0) {
		glm::vec2 collisionDepthVector = glm::normalize(distance) * (MinimunDistance - collisionDistance);

		_position += collisionDepthVector / 2.0f;
		actor->_position -= collisionDepthVector / 2.0f;
		return true;
	}
	return false;
}
void Actor::CheckTilePosition(const std::vector<std::string>& levelData,
	std::vector<glm::vec2>& collideTilePositions,
	float cornerPositionX, float cornerPositionY) {
	// Check the for corners.
	glm::vec2 cornerPosition = glm::vec2(floor(cornerPositionX / ActorWidth),
		floor(cornerPositionY / ActorWidth));

	// If the actor is swapned out side the world then just return.
	if (cornerPosition.x < 0 || cornerPosition.x >= levelData[0].size() ||
		cornerPosition.y < 0 || cornerPosition.y >= levelData.size() ) {
		return;
	}

	if (levelData[cornerPosition.y][cornerPosition.x] != '.') {
		collideTilePositions.push_back(cornerPosition * ActorWidth + glm::vec2(ActorWidth / 2.0f, ActorWidth / 2.0f));
	}
}

// Axis-Aligned Bounding Box collision.
void Actor::CollideWithTile(glm::vec2 tilePosition) {
	const float TileRadius = ActorWidth / 2.0f;
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