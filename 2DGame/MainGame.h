#pragma once
#include <SDL\SDL.h>
#include <GL\glew.h>
#include <vector>

#include <GameEngine\GameEngine.h>
#include <GameEngine\Window.h>
#include <GameEngine\GLSLProgram.h>
#include <GameEngine\Sprite.h>
#include <GameEngine\Camera2D.h>
#include <GameEngine\SpriteBatch.h>
#include <GameEngine\InputManager.h>
#include <GameEngine\Timer.h>

#include "Projectile.h"

	enum GameState {
		PLAY,
		EXIT
	};

	class MainGame
	{
	public:
		MainGame();
		~MainGame();

		void RunGame();
	private:
		void InitGame();
		void InitShaders();
		void ProcessInput();
		void ProcessKeyBoardInput();
		void ProcessMouseInput();
		void LoopGame();
		void DrawGame();

		void Experimental_ImmediateMode();

		// The size of the game window.
		int _screenWidth;
		int _screenHeight;

		// The window.
		GameEngine::Window _window;

		// Recode current game state.
		GameState _currentGameState;

		// The shaders.
		float _time;
		GameEngine::GLSLProgram _shaderProgram;

		// All the sprites (No longer need it any more because of the sprite batch function.)
		// std::vector<GameEngine::Sprite*> _sprites;

		// The 2d camera
		GameEngine::Camera2D _camera2D;

		GameEngine::SpriteBatch _spriteBatch;

		GameEngine::InputManager _inputManager;

		GameEngine::FpsLimiter _fpsLimiter;
		float _targetFPS;

		std::vector<Projectile> _bullets;
	};
