#pragma once

#include <string>
#include <vector>

#include <GameEngine/SpriteBatch.h>

const int TILE_WIDTH = 100;

class Level
{
public:
    // Load the level
    Level(const std::string& fileName);
    ~Level();

    void draw();

    int getWidth() const { return _levelData[0].size(); }
    int getHeight() const { return _levelData.size(); }
    int getNumShips() const { return _numShips; }
    const std::vector<std::string>& getLevelData() const { return _levelData; }
    glm::vec2 getStartPlayerPos() const { return _startPlayerPos; }
    const std::vector<glm::vec2>& getUFOStartPositions() const { return _zombieStartPositions; }

private:
    std::vector<std::string> _levelData;
    int _numShips;
	GameEngine::SpriteBatch _spriteBatch;

    glm::vec2 _startPlayerPos;
    std::vector<glm::vec2> _zombieStartPositions;
};

