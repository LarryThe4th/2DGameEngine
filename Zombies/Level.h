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
	const std::vector<glm::vec2>& GetZombieSwapnPositions() const { return _zombieSpawnPosition; }
	unsigned int GetSquareTileSize() const { return _tileSize; }
	const std::vector<std::string>& GetLevelData() const { return _levelData; }

	// Setters 
	void SetSquareTileSize(unsigned int size) {  _tileSize = size; }

private:
	void InitLevelSprites();

	unsigned int _tileSize;

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

