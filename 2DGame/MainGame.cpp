#include "MainGame.h"
#include <GameEngine\ResourceManager.h>
#include <iostream>

	// Consturctor, initializes private member variables
	MainGame::MainGame() :
		_screenWidth(1024),
		_screenHeight(768),
		_currentGameState(GameState::PLAY),
		_time(0.0f),
		_targetFPS(60.0f)
	{
		_camera2D.InitCamera(_screenWidth, _screenHeight);
	}

	// Destructor, not going to do anything right now.
	MainGame::~MainGame()
	{
	}

	// Initialize SDL and Opengl and whatever else we need.
	void MainGame::InitGame() {

		// Initialize the game engine.
		GameEngine::InitEngine();

		// Create a SDL window.
		// Notice that the window mode MUST include SDL_WINDOW_OPENGL for use with OpenGL.
		_window.CreateWindow("2D Game", _screenWidth, _screenHeight, GameEngine::WINDOWMODE);

		// Initialize the shaders
		InitShaders();

		// Initialize the sprite batch.
		_spriteBatch.InitSpriteBatch();

		// Initialize the fps limiter.
		_fpsLimiter.InitFpsLimiter(_targetFPS);
	}

	void MainGame::InitShaders() {
		_shaderProgram.CompileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
		_shaderProgram.AddAttribute("vertexPosition");
		_shaderProgram.AddAttribute("vertexColor");
		_shaderProgram.AddAttribute("vertexUV");
		_shaderProgram.LinkShaders();
	}

	// Run the game.
	void MainGame::RunGame() {
		InitGame();
		// This only stop (Or say return) when the game ends.
		LoopGame();
	}

	// Processes input with SDL
	void MainGame::ProcessInput() {
		SDL_Event sdlEvent;
		// Will keep looping until there are no more events to process
		while (SDL_PollEvent(&sdlEvent))
		{
			switch (sdlEvent.type)
			{
			case SDL_KEYDOWN:
				_inputManager.KeyPressed(sdlEvent.key.keysym.sym);
				break;
			case SDL_KEYUP:
				_inputManager.KeyReleased(sdlEvent.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.KeyPressed(sdlEvent.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.KeyReleased(sdlEvent.button.button);
				break;
			case SDL_QUIT:
				_currentGameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				_inputManager.SetMouseScreenCoordinate((float)sdlEvent.motion.x, (float)sdlEvent.motion.y);
				break;
			default:
				break;
			}
		}
		// Process the key board input.
		ProcessKeyBoardInput();

		ProcessMouseInput();
	}

	// Separate the key board part and the mouse motion part to make the code looks more clean.
	void MainGame::ProcessKeyBoardInput() {

		if (_inputManager.IsKeyPressed(SDLK_w)) {
			_camera2D.SetCameraPosition(_camera2D.GetCameraPosition() + glm::vec2(0.0f, -20.0f));
		}

		if (_inputManager.IsKeyPressed(SDLK_s)) {
			_camera2D.SetCameraPosition(_camera2D.GetCameraPosition() + glm::vec2(0.0f, 20.0f));
		}

		if (_inputManager.IsKeyPressed(SDLK_a)) {
			_camera2D.SetCameraPosition(_camera2D.GetCameraPosition() + glm::vec2(20.0f, 0.0f));
		}

		if (_inputManager.IsKeyPressed(SDLK_d)) {
			_camera2D.SetCameraPosition(_camera2D.GetCameraPosition() + glm::vec2(-20.0f, 0.0f));
		}

		if (_inputManager.IsKeyPressed(SDLK_ESCAPE)) {
			_currentGameState = GameState::EXIT;
			return;
		}
	}

	// This handles all the mouse related user input such as clicks and motions.
	void MainGame::ProcessMouseInput() {
		if (_inputManager.IsKeyPressed(SDL_BUTTON_LEFT)) {
			glm::vec2 mouseWorldCoordinate = _camera2D.GetWorldFormScreen(_inputManager.GetMouseScreenCoordinate());
			// std::cout << "X pos: " << mouseCoords.x << " Y pos: " << mouseCoords.y << std::endl;
			glm::vec2 playPosition(0.0f);
			glm::vec2 mouseToPlayerDirection = mouseWorldCoordinate - playPosition;
			mouseToPlayerDirection = glm::normalize(mouseToPlayerDirection);

			_bullets.emplace_back(5.0f, playPosition, mouseToPlayerDirection, 1000);
		}
	}

	// This is where the magics happens :)
	void MainGame::LoopGame() {
		while (_currentGameState != GameState::EXIT)
		{
			_fpsLimiter.OnFrameBegin();

			// Process the user input, this have to be call befor the drawGame() function.
			ProcessInput();

			// Temporary, im going to remove this ASAP.
			_time += 0.1f;

			// Update the camera.
			_camera2D.UpdateCamera();

			// Update all the bullets.
			for (unsigned int i = 0; i < _bullets.size();) {
				_bullets[i].UpdateProjectile();
				if (_bullets[i].IsLifeTimePassed()) {
					// Overwrite the current vector element by the last element in the vector.
					_bullets[i] = _bullets.back();
					// Then Removes the last element in the vector.
					_bullets.pop_back();
				}
				else
				{
					i++;
				}
			}

			// Draw the game!
			DrawGame();

			_fpsLimiter.OnFrameEnd();
		}
	}

	// Draw the game using the almighty Opengl god!
	void MainGame::DrawGame() {
		// "glClearDepth" specifies the depth value used by glClear to clear the depth buffer. 
		// Values specified by "glClearDepth" are clamped to the range 0 1 .
		glClearDepth(1.0f);

		// Clear the color and depth buffer at once using binary operation.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Enable the shader program.
		_shaderProgram.UseShader();

		// We are using the texture unit 0.
		glActiveTexture(GL_TEXTURE0);

		// Set the constantly changing time variable.
		GLint timeLocation = _shaderProgram.GetUniformLocation("time");
		glUniform1f(timeLocation, _time);

		// Get the uniform location.
		GLint TextureLocation = _shaderProgram.GetUniformLocation("mySampler");
		// Tell the shader that the texture is in the texture unit 0.
		glUniform1f(TextureLocation, 0);

		// Set the ortho matrix location.
		GLint orthoMatrixLocation = _shaderProgram.GetUniformLocation("orthographicProjectionMatrix");
		glm::mat4 cameraMatrix = _camera2D.GetCameraMatrix();
		// The uniform location will be the orthoMatrixLocation, and the count of matrixs will be 1.
		// No transpose, and the pointer to the camera matrix data just like a array.
		glUniformMatrix4fv(orthoMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

		_spriteBatch.Begin();

		// origin position x, origin position y, size width and size height.
		static GameEngine::GLTexture texture = GameEngine::ResourceManager::GetTexture("Textures/Fallout.png");
		static glm::vec4 positionAndSize(0.0f, 0.0f, 150.0f, 150.0f);
		static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
		static GameEngine::Color color;
		color.red = 225;
		color.green = 225;
		color.blue = 225;
		color.alpha = 225;

		_spriteBatch.AddSprite(positionAndSize, uv, texture.id, 0.0f, color);

		for (unsigned int i = 0; i < _bullets.size(); i++) {
			_bullets[i].AddProjectile(_spriteBatch);
		}

		_spriteBatch.End();

		_spriteBatch.RenderBatches();


		/* Becuase of now we have a sprite batch function so no need to loop through the DrawSprite method.
		// Draw the sprites.
		for (unsigned int i = 0; i < _sprites.size(); i++)
		{
			_sprites[i]->DrawSprite();
		}
		*/

		// unbind the texture.
		glBindTexture(GL_TEXTURE_2D, 0);

		// Disable the shader program.
		_shaderProgram.UnuseShader();

		// Swap our buffer and draw everything to the screen.
		_window.SwapBuffer();
	}

	// Learn something about the outdated immediate mode.
	void MainGame::Experimental_ImmediateMode() {
		// Set the color we want to use.(Only works under immediate mode)
		glEnableClientState(GL_COLOR_ARRAY);

		// Draw a triangle using the shitty immediate mode cause this is obsoleted.
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-1, -1);
		glVertex2f(0, -1);
		glVertex2f(0, 0);
		glEnd();
	}
