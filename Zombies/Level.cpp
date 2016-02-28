#include "Level.h"
#include <GameEngine\ErrorMessage.h>
#include <GameEngine\ResourceManager.h>
#include <fstream>
#include <iostream>
#include <algorithm>

Level::Level() :
	_tileSize(32),
	_numHumans(0)
{
}

Level::~Level()
{
}

void Level::InitLevel(const std::string& filePath) {
	// Load the file.
	std::ifstream levelDataFile;
	levelDataFile.open(filePath);
	if (levelDataFile.fail()) {
		GameEngine::FatalError("Failed to load file!" + filePath);
	}

	// Throw away the first string in temp;
	std::string temp;
	levelDataFile >> temp >> _numHumans;

	// Store the data in the vector.
	while (std::getline(levelDataFile, temp)) {
		_levelData.push_back(temp);
	}

	std::reverse(_levelData.begin(), _levelData.end());

	InitLevelSprites();
}

void Level::InitLevelSprites() {
	_spriteBatch.InitSpriteBatch();
	_spriteBatch.Begin();
	// Basic settings of a sprite.
	const int SpriteSizeWidth = 32;
	const glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	GameEngine::Color color;
	color.red = 225;
	color.green = 225;
	color.blue = 225;
	color.alpha = 225;

	for (size_t y = 0; y < _levelData.size(); y++)
	{
		for (size_t x = 0; x < _levelData[y].size(); x++)
		{
			// Take each individual tile information form the level data.
			char tile = _levelData[y][x];

			// The position and size of the sprite.
			glm::vec4 positionAndSize(x * SpriteSizeWidth, y * SpriteSizeWidth,
				SpriteSizeWidth, SpriteSizeWidth);
			// Process the tile.
			switch (tile)
			{
				// Store the player spawn position for later use.
				case '@':
					_levelData[y][x] = '.';
					_playerSpawnPosition.x = x * SpriteSizeWidth;
					_playerSpawnPosition.y = y * SpriteSizeWidth;
					break;
				// Store the player spawn position for later use.
				case 'Z':
					_levelData[y][x] = '.';
					_zombieSpawnPosition.emplace_back(x * SpriteSizeWidth, y * SpriteSizeWidth);
					break;
				// The unwalkable red bricks.
				case 'R':
					_spriteBatch.AddSprite(positionAndSize,
						uv,
						GameEngine::ResourceManager::GetTexture("Textures/red_bricks.png").id,
						0.0f,
						color);
					break;
				// The unwalkable light bricks.
				case 'L':
					_spriteBatch.AddSprite(positionAndSize,
						uv,
						GameEngine::ResourceManager::GetTexture("Textures/light_bricks.png").id,
						0.0f,
						color);
					break;
				// The glass.
				case 'G':
					_spriteBatch.AddSprite(positionAndSize,
						uv,
						GameEngine::ResourceManager::GetTexture("Textures/glass.png").id,
						0.0f,
						color);
					break;
				// The ground.
				case '.':
					break;
				case 'B':
					_spriteBatch.AddSprite(positionAndSize,
						uv,
						GameEngine::ResourceManager::GetTexture("Textures/red_bricks.png").id,
						0.0f,
						color);
					break;
				default:
					std::printf("Unexpected symbol %C at (%d, %d).\n", tile, x, y);
					GameEngine::FatalError("Unexpected symbol during level data loading.");
					break;
			}
		}
	}

	_spriteBatch.End();
}

void Level::DrawLevel() {
	_spriteBatch.RenderBatches();
}