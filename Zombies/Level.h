#pragma once
#include <glm\glm.hpp>
#include <string>
#include <vector>
#include <GameEngine\SpriteBatch.h>

class Level
{
public:
	// Load the level.
	Level();
	~Level();

	void InitLevel(const std::string& filePath);
	void DrawLevel();

	// Getters
	glm::vec2 GetPlayerSwapnPosition() const { return _playerSpawnPosition; }
	const std::vector<glm::vec2>& GetZombiesSwapnPosition() const { return _zombieSpawnPosition; }


private:
	void InitLevelSprites();

	// A list of strings holds the data of the level. 
	std::vector<std::string> _levelData;
	// The number of humans in the level.
	int _numHumans;

	GameEngine::SpriteBatch _spriteBatch;

	// glm::ivec2 is stand for "2 int elements in vector".
	glm::vec2 _playerSpawnPosition;

	// The spawn positions for the zombies.
	std::vector<glm::vec2> _zombieSpawnPosition;
};

