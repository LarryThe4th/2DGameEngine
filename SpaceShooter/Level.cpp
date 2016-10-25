#include "Level.h"

#include <GameEngine/ErrorMessage.h>
#include <fstream>
#include <iostream>
#include <GameEngine/ResourceManager.h>

Level::Level(const std::string& fileName) {

    std::ifstream file;
    file.open(fileName);

    // Error checking
    if (file.fail()) {
		GameEngine::FatalError("Failed to open " + fileName);
    }

    // Throw away the first string in tmp
    std::string tmp;

    file >> tmp >> _numShips;

    std::getline(file, tmp); // Throw away the rest of the first line

    // Read the level data
    while (std::getline(file, tmp)) {
        _levelData.push_back(tmp);
    }    
    
    _spriteBatch.InitSpriteBatch();
    _spriteBatch.Begin();

    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

	GameEngine::Color whiteColor;
    whiteColor.red = 255;
    whiteColor.green = 255;
    whiteColor.blue = 255;
    whiteColor.alpha = 255;

    // Render all the tiles
    for (size_t y = 0; y < _levelData.size(); y++) {
        for (size_t x = 0; x < _levelData[y].size(); x++) {
            // Grab the tile
            char tile = _levelData[y][x];

            // Get dest rect
            glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

            // Process the tile
            switch (tile) {
                case 'B':
                case 'R':
                    _spriteBatch.AddSprite(destRect,
                                      uvRect,
                                      GameEngine::ResourceManager::GetTexture("Textures/Bricks.png").id,
                                      0.0f,
                                      whiteColor);      
                    break;
                case 'G':
                    _spriteBatch.AddSprite(destRect,
                                      uvRect,
						GameEngine::ResourceManager::GetTexture("Textures/Bricks3.png").id,
                                      0.0f,
                                      whiteColor);
                    break;
                case 'L':
                    _spriteBatch.AddSprite(destRect,
                                      uvRect,
						GameEngine::ResourceManager::GetTexture("Textures/Bricks4.png").id,
                                      0.0f,
                                      whiteColor);
                    break;
                case '@':
                    _levelData[y][x] = '.'; /// So we dont collide with a @
                    _startPlayerPos.x = (float)(x * TILE_WIDTH);
                    _startPlayerPos.y = (float)(y * TILE_WIDTH);
                    break;
                case 'Z':
                    _levelData[y][x] = '.'; /// So we dont collide with a Z
                    _zombieStartPositions.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
                    break;
                case '.':
                    break;
                default:
                    std::printf("Unexpected symbol %c at (%d,%d)", tile, x, y);
                    break;
            }
        }
    }

    _spriteBatch.End();

}


Level::~Level()
{
}


void Level::draw() {
    _spriteBatch.RenderBatches();
}