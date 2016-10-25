#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>

#include <GameEngine\GameEngine.h>
#include <GameEngine\Window.h>
#include <GameEngine\GLSLProgram.h>
#include <GameEngine\InputManager.h>
#include <GameEngine\Camera2D.h>
#include <GameEngine\Timer.h>
#include <GameEngine\SpriteBatch.h>

#include "Level.h"
#include "Player.h"
#include "Zombie.h"

const float player_MoveSpeed = 8.0f;
const float zombies_MoveSpeed = 1.5f;
const float human_MoveSpeed = 1.0f;

class Zombie;

class MainGame
{
	enum GameState {
		PLAY,
		EXIT
	};

	public:
		MainGame();
		~MainGame();

		void RunGame();

	private:
		void InitGame();
		void InitShaders();
		void InitLevels();
		void UpdateActors();
		void DrawActors();
		void LoopGame();
		void ProcessInput();
		void DrawGame();

		// Keep tacking the game state.
		GameState _currentGameState;

		// The camera.
		GameEngine::Camera2D _camera;

		// Handles all the user input.
		GameEngine::InputManager _inputManager;
		void ProcessKeyBoardInput();
		void ProcessMouseInput();

		// This handle all the textures.
		GameEngine::GLSLProgram _textureProgram;

		// A vector of different levels data.
		std::vector<Level*> _levels;
		int _currentLevelIndex;
		void DeleteLevelData();

		GameEngine::SpriteBatch _actorsSpriteBatch;

		// All the humans.
		void InitHumans();
		std::vector<Human*> _humans;
		void DeleteHumans();

		// Zombies.
		void InitZombies();
		std::vector<Zombie*> _zombies;

		// The player.
		Player* _player;
		void InitPlayer();

		// The game window.
		GameEngine::Window* _window = new GameEngine::Window;
		void DeleteWindow();
		int _screenWidth;
		int _screenHeight;

		// Limit the fps.
		GameEngine::FpsLimiter _fpsLimiter;
};