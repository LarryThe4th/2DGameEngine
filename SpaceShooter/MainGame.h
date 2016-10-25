#pragma once

#include <GameEngine/Window.h>
#include <GameEngine/GLSLProgram.h>
#include <GameEngine/Camera2D.h>
#include <GameEngine/InputManager.h>
#include <GameEngine/SpriteBatch.h>

#include "Player.h"
#include "Level.h"
#include "Bullet.h"

class UFO;

enum class GameState {
    PLAY,
    EXIT
};

class MainGame
{
public:
    MainGame();
    ~MainGame();

    // Runs the game
    void run();

private:
    // Initializes the core systems
    void initSystems();

    // Initializes the level and sets up everything
    void initLevel();

    // Initializes the shaders
    void initShaders();

    // Main game loop for the program
    void gameLoop();

    // Updates all agents
    void updateAgents();

    // Updates all bullets
    void updateBullets();

    // Checks the victory condition
    void checkVictory();

    // Handles input processing
    void processInput();

    // Renders the game
    void drawGame();

    // Member Variables
	// The game window
	GameEngine::Window _window;
    
	// The shader program
	GameEngine::GLSLProgram _textureProgram; 

	// Handles input
	GameEngine::InputManager _inputManager;

	// Main Camera
	GameEngine::Camera2D _camera;

	// Draws all agents
	GameEngine::SpriteBatch _agentSpriteBatch; 

	// vector of all levels
    std::vector<Level*> _levels;

    int _screenWidth, _screenHeight;

    float _fps;

    int _currentLevel;

    Player* _player;
	// Vector of all ships
    std::vector<SpaceShip*> _Ships; 
	// Vector of all UFO
    std::vector<UFO*> _UFOs; 
	// Vector of all bullets
    std::vector<Bullet> _bullets;

	// A counter of ships killed by player
    int _numShipsKilled;
	// A counter of UFOs killed by player
    int _numUFOKilled;

    GameState _gameState;
};

