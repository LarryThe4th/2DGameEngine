#include "MainGame.h"

#include <GameEngine/GameEngine.h>
#include <GameEngine/Timer.h>
#include <GameEngine/ErrorMessage.h>
#include <random>
#include <ctime>

#include <SDL/SDL.h>
#include <iostream>

#include "Gun.h"
#include "UFO.h"

const float SHIP_SPEED = 1.0f;
const float UFO_SPEED = 3.0f;
const float PLAYER_SPEED = 5.0f;

MainGame::MainGame()  :
    _screenWidth(1024),
    _screenHeight(768),
    _gameState(GameState::PLAY),
    _fps(0),
    _player(nullptr),
    _numShipsKilled(0),
    _numUFOKilled(0) {
    // Empty
}

MainGame::~MainGame() {
    // Don't forget to delete the levels!
    for (size_t i = 0; i < _levels.size(); i++) {
        delete _levels[i];
    }
    // Don't forget to delete all the agents!
    for (size_t i = 0; i < _Ships.size(); i++) {
        delete _Ships[i];
    }
    for (size_t i = 0; i < _UFOs.size(); i++) {
        delete _UFOs[i];
    }
}

void MainGame::run() {

    initSystems();

    initLevel();

    gameLoop();
}

void MainGame::initSystems() {
    // Initialize the game engine
    GameEngine::InitEngine();

    // Create our window
    _window.CreateWindow("Space Shooter", _screenWidth, _screenHeight, 0);

    // Grey background color
    glClearColor(64 / 225, 64 / 225, 64 / 225, 1.0f);

    // Set up the shaders
    initShaders();

    // Initialize our spritebatch
    _agentSpriteBatch.InitSpriteBatch();

    // Set up the camera
    _camera.InitCamera(_screenWidth, _screenHeight);

	// Zoom out the camera by 2 times.
	const float CAMERA_SCALE = 1.0f / 2.0f;
	_camera.SetCameraScale(CAMERA_SCALE);

}

void MainGame::initLevel() {
    // Level 1
    _levels.push_back(new Level("Levels/Level_02.txt"));
    _currentLevel = 0;

    _player = new Player();
    _player->init(PLAYER_SPEED, _levels[_currentLevel]->getStartPlayerPos(), &_inputManager, &_camera, &_bullets);

	// All the player into the list of ships
    _Ships.push_back(_player);

    std::mt19937 randomEngine;
    randomEngine.seed(time(nullptr));

    std::uniform_int_distribution<int> randX(2, _levels[_currentLevel]->getWidth() - 2);
    std::uniform_int_distribution<int> randY(2, _levels[_currentLevel]->getHeight() - 2);

    // Add all the random ships
    for (int i = 0; i < _levels[_currentLevel]->getNumShips(); i++) {
        _Ships.push_back(new SpaceShip);
        glm::vec2 pos(randX(randomEngine) * TILE_WIDTH, randY(randomEngine) * TILE_WIDTH);
        _Ships.back()->init(SHIP_SPEED, pos);
    }

    // Add the UFO
    const std::vector<glm::vec2>& UFOPositions = _levels[_currentLevel]->getUFOStartPositions();
    for (size_t i = 0; i < UFOPositions.size(); i++) {
        _UFOs.push_back(new UFO);
        _UFOs.back()->init(UFO_SPEED, UFOPositions[i]);
    }

    // Set up the players guns
    const float BULLET_SPEED = 20.0f;
    _player->addGun(new Gun("Missle", 20, 1, 5.0f, 30, BULLET_SPEED));
}

void MainGame::initShaders() {
    // Compile our color shader
    _textureProgram.CompileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
    _textureProgram.AddAttribute("vertexPosition");
    _textureProgram.AddAttribute("vertexColor");
    _textureProgram.AddAttribute("vertexUV");
    _textureProgram.LinkShaders();
}

void MainGame::gameLoop() {
    
    GameEngine::FpsLimiter fpsLimiter;
    fpsLimiter.SetTargetFPS(60.0f);

    // Main loop
    while (_gameState == GameState::PLAY) {
        fpsLimiter.OnFrameBegin();

        checkVictory();

        processInput();
       
        updateAgents();

        updateBullets();

        _camera.SetCameraPosition(_player->getPosition());

        _camera.UpdateCamera();

        drawGame();

        _fps = fpsLimiter.OnFrameEnd();
    }
}

void MainGame::updateAgents() {
    // Update all ships
    for (size_t i = 0; i < _Ships.size(); i++) {
        _Ships[i]->update(_levels[_currentLevel]->getLevelData(),
                           _Ships,
                           _UFOs);
    }

    // Update all UFO
    for (size_t i = 0; i < _UFOs.size(); i++) {
        _UFOs[i]->update(_levels[_currentLevel]->getLevelData(),
                           _Ships,
                           _UFOs);
    }

    // Update UFO collisions
    for (size_t i = 0; i < _UFOs.size(); i++) {
        // Collide with other UFOs
        for (size_t j = i + 1; j < _UFOs.size(); j++) {
            _UFOs[i]->collideWithAgent(_UFOs[j]);
        }
        // Collide with ships
        for (size_t j = 1; j < _Ships.size(); j++) {
            if (_UFOs[i]->collideWithAgent(_Ships[j])) {
                // Add the new zombie
                _UFOs.push_back(new UFO);
                _UFOs.back()->init(UFO_SPEED, _Ships[j]->getPosition());
                // Delete the ships
                delete _Ships[j];
                _Ships[j] = _Ships.back();
                _Ships.pop_back();
            }
        }

        // Collide with player
        if (_UFOs[i]->collideWithAgent(_player)) {
            GameEngine::FatalError("YOU LOSE");
        }
    }

    // Update space ship collisions
    for (size_t i = 0; i < _Ships.size(); i++) {
        // Collide with other ships
        for (size_t j = i + 1; j < _Ships.size(); j++) {
            _Ships[i]->collideWithAgent(_Ships[j]);
        }
    }
}

void MainGame::updateBullets() {
    // Update and collide with world
    for (size_t i = 0; i < _bullets.size(); ) {
        // If update returns true, the bullet collided with a wall
        if (_bullets[i].update(_levels[_currentLevel]->getLevelData())) {
            _bullets[i] = _bullets.back();
            _bullets.pop_back();
        } else {
            i++;
        }
    }

	// Check if the bullet has been removed.
    bool wasBulletRemoved;

    // Collide with space ships and UFOs
    for (size_t i = 0; i < _bullets.size(); i++) {
        wasBulletRemoved = false;
        // Loop through zombies
        for (size_t j = 0; j < _UFOs.size(); ) {
            // Check collision
            if (_bullets[i].collideWithAgent(_UFOs[j])) {
                // Damage enemy UFO, and kill it if its out of health
                if (_UFOs[j]->applyDamage(_bullets[i].getDamage())) {
                    // If the zombie died, remove him
                    delete _UFOs[j];
                    _UFOs[j] = _UFOs.back();
                    _UFOs.pop_back();
                    _numUFOKilled++;
                } else {
                    j++;
                }

                // Remove the bullet
                _bullets[i] = _bullets.back();
                _bullets.pop_back();
                wasBulletRemoved = true;
                i--; // Make sure we don't skip a bullet
                // Since the bullet was used, no need to loop through any more targets.
                break;
            } else {
                j++;
            }
        }
        // Loop through ships
        if (wasBulletRemoved == false) {
            for (size_t j = 1; j < _Ships.size(); ) {
                // Check collision
                if (_bullets[i].collideWithAgent(_Ships[j])) {
                    // Damage ship, and kill it if its out of health
                    if (_Ships[j]->applyDamage(_bullets[i].getDamage())) {
                        // If the ship died, remove that ship
                        delete _Ships[j];
                        _Ships[j] = _Ships.back();
                        _Ships.pop_back();
                    } else {
                        j++;
                    }

                    // Remove the bullet
                    _bullets[i] = _bullets.back();
                    _bullets.pop_back();
                    _numShipsKilled++;
                    i--; // Make sure we don't skip a bullet
                    // Since the bullet was used, no need to loop through any more targets.
                    break;
                } else {
                    j++;
                }
            }
        }
    }
}

void MainGame::checkVictory() {
    // If all enemy UFO are dead we win!
    if (_UFOs.empty()) {
        // Print victory message
        std::printf("*** You win! ***\n You killed %d ships and %d UFOs. There are %d/%d ship remaining",
                    _numShipsKilled, _numUFOKilled, _Ships.size() - 1, _levels[_currentLevel]->getNumShips());

        // Easy way to end the game :P
        GameEngine::FatalError("");
    }
}

void MainGame::processInput() {
    SDL_Event evnt;
    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                _inputManager.SetMouseScreenCoordinate(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManager.KeyPressed(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.KeyReleased(evnt.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                _inputManager.KeyPressed(evnt.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                _inputManager.KeyReleased(evnt.button.button);
                break;
        }
    }
}

void MainGame::drawGame() {
    // Set the base depth to 1.0
    glClearDepth(1.0);
    // Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _textureProgram.UseShader();

    // Draw code goes here
    glActiveTexture(GL_TEXTURE0);

    // Make sure the shader uses texture 0
    GLint textureUniform = _textureProgram.GetUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    glm::mat4 projectionMatrix = _camera.GetCameraMatrix();
    GLint pUniform = _textureProgram.GetUniformLocation("P");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Draw the level
    _levels[_currentLevel]->draw();

    // Begin drawing agents
    _agentSpriteBatch.Begin();

    // Draw the ships
    for (size_t i = 0; i < _Ships.size(); i++) {
		_Ships[i]->draw(_agentSpriteBatch);	
    }

    // Draw the UFOs
    for (size_t i = 0; i < _UFOs.size(); i++) {
        _UFOs[i]->draw(_agentSpriteBatch);
    }

    // Draw the bullets
    for (size_t i = 0; i < _bullets.size(); i++) {
        _bullets[i].draw(_agentSpriteBatch);
    }

    // End spritebatch creation
    _agentSpriteBatch.End();

    // Render to the screen
    _agentSpriteBatch.RenderBatches();

    // Unbind the program
    _textureProgram.UseShader();

    // Swap our buffer and draw everything to the screen!
    _window.SwapBuffer();
}