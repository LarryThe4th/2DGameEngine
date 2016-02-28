#include "MainGame.h"

// Consturctor, initializes private member variables
MainGame::MainGame() :
	_screenWidth(1024),
	_screenHeight(768),
	_currentGameState(GameState::PLAY),
	_currentLevelIndex(0),
	_player(nullptr)
{
}

// Destructor, not going to do anything right now.
MainGame::~MainGame()
{
	// Delete all instance for Preventing Memory Leaks.
	DeleteLevelData();
	DeleteWindow();
	DeleteHumans();
}

void MainGame::InitGame() {
	// Initializes the engine.
	GameEngine::InitEngine();

	// Create the window.
	_window->CreateWindow("Zombie War", _screenWidth, _screenHeight, GameEngine::WINDOWMODE);

	// Initializes the camera.
	_camera.InitCamera(_screenWidth, _screenHeight);

	// Initializes the shaders.
	InitShaders();

	// Initializes the fps limiter and set the maximun fps to 60.
	_fpsLimiter.InitFpsLimiter();

	_humansSpriteBatch.InitSpriteBatch();
}

void MainGame::InitShaders() {
	_textureProgram.CompileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	_textureProgram.AddAttribute("vertexPosition");
	_textureProgram.AddAttribute("vertexColor");
	_textureProgram.AddAttribute("vertexUV");
	_textureProgram.LinkShaders();
}

void MainGame::InitLevels() {
	Level* newLevel = new Level;
	newLevel->InitLevel("Levels/Level_01.txt");
	_levels.push_back(newLevel);
}

void MainGame::InitPlayer() {
	_player = new Player;
	_player->InitPlayer(_levels[_currentLevelIndex]->GetPlayerSwapnPosition(), 8.0f, &_inputManager);
	_humans.push_back(_player);
}

void MainGame::RunGame() {
	InitGame();

	// Initializes a new game level.
	InitLevels();

	// Initializes a new player.
	// This have to do after InitLevels() becuase we need the player swapn position.
	InitPlayer();

	LoopGame();
}

void MainGame::LoopGame() {
	while(_currentGameState == GameState::PLAY) {

		_fpsLimiter.OnFrameBegin();

		ProcessInput();

		UpdateActors();

		_camera.SetCameraPosition(_player->GetActorPosition());
		_camera.UpdateCamera();

		DrawGame();

<<<<<<< HEAD
		_fpsLimiter.FpsCounter();
=======
		// _fpsLimiter.FpsCounter();
>>>>>>> refs/remotes/origin/backUp
		_fpsLimiter.OnFrameEnd();
	}
}

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

	ProcessKeyBoardInput();
	// ProcessMouseInput();
}

void MainGame::UpdateActors() {
	// Draw the player.
	for (size_t i = 0; i < _humans.size(); i++)
	{
<<<<<<< HEAD
		_humans[i]->Update();
=======
		_humans[i]->Update(_levels[_currentLevelIndex]->GetLevelData(),
							_humans,
							_zombies);
>>>>>>> refs/remotes/origin/backUp
	}
}

void MainGame::DrawActors() {
	_humansSpriteBatch.Begin();

	// Draw the player.
	for (size_t i = 0; i < _humans.size(); i++)
	{
		_humans[i]->AddActor(_humansSpriteBatch);
	}

	_humansSpriteBatch.End();

	_humansSpriteBatch.RenderBatches();
}

void MainGame::DrawGame() {
	// Set the base depth to 1.0.
	glClearDepth(1.0f);
	// Clear the color and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable the shader program.
	_textureProgram.UseShader();

	// Active the texture.
	glActiveTexture(GL_TEXTURE0);

	// Make sure the shader uses texture 0.
	GLuint textureUniform = _textureProgram.GetUniformLocation("mySampler");
	glUniform1f(textureUniform, 0.0f);

	// Set the ortho matrix location.
	GLint orthoMatrixLocation = _textureProgram.GetUniformLocation("orthographicProjectionMatrix");
	glm::mat4 cameraMatrix = _camera.GetCameraMatrix();
	// The uniform location will be the orthoMatrixLocation, and the count of matrixs will be 1.
	// No transpose, and the pointer to the camera matrix data just like a array.
	glUniformMatrix4fv(orthoMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	// Draw the level.
	_levels[_currentLevelIndex]->DrawLevel();

	// Draw all the actors.
	DrawActors();

	// unbind the texture.
	glBindTexture(GL_TEXTURE_2D, 0);

	// Disable the shader program.
	_textureProgram.UnuseShader();

	// Swap our buffer and draw everything to the screen.
	_window->SwapBuffer();
}

void MainGame::DeleteLevelData() {
	for (size_t i = 0; i < _levels.size(); i++) {
		delete _levels[i];
	}
	_levels.clear();
}

void MainGame::DeleteWindow() {
	delete _window;
}

void MainGame::DeleteHumans() {
	for (size_t i = 0; i < _humans.size(); i++)
	{
		delete _humans[i];
	}
	_humans.clear();
}

// Separate the key board part and the mouse motion part to make the code looks more clean.
void MainGame::ProcessKeyBoardInput() {

	//if (_inputManager.IsKeyPressed(SDLK_w)) {
	//	_camera.SetCameraPosition(_camera.GetCameraPosition() + glm::vec2(0.0f, 20.0f));
	//}

	//if (_inputManager.IsKeyPressed(SDLK_s)) {
	//	_camera.SetCameraPosition(_camera.GetCameraPosition() + glm::vec2(0.0f, -20.0f));
	//}

	//if (_inputManager.IsKeyPressed(SDLK_a)) {
	//	_camera.SetCameraPosition(_camera.GetCameraPosition() + glm::vec2(-20.0f, 0.0f));
	//}

	//if (_inputManager.IsKeyPressed(SDLK_d)) {
	//	_camera.SetCameraPosition(_camera.GetCameraPosition() + glm::vec2(20.0f, 0.0f));
	//}

	if (_inputManager.IsKeyPressed(SDLK_ESCAPE)) {
		_currentGameState = GameState::EXIT;
		return;
	}
}

// This handles all the mouse related user input such as clicks and motions.
void MainGame::ProcessMouseInput() {
	//if (_inputManager.IsKeyPressed(SDL_BUTTON_LEFT)) {
	//	glm::vec2 mouseWorldCoordinate = _camera.GetWorldFormScreen(_inputManager.GetMouseScreenCoordinate());
	//	// std::cout << "X pos: " << mouseCoords.x << " Y pos: " << mouseCoords.y << std::endl;
	//	glm::vec2 playPosition(0.0f);
	//	glm::vec2 mouseToPlayerDirection = mouseWorldCoordinate - playPosition;
	//	mouseToPlayerDirection = glm::normalize(mouseToPlayerDirection);

	//	_bullets.emplace_back(5.0f, playPosition, mouseToPlayerDirection, 1000);
	//}
}