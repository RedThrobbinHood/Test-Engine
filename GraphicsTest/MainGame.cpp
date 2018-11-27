#include "MainGame.h"
#include "Sprite.h"
#include "Errors.h"

#include <iostream>
#include <string>


MainGame::MainGame()
{
	_window = nullptr;
	_screenWidth = 1024;
	_screenHeight = 768;
	_gameState = GameState::PLAY;
}


MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();

	_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
	gameLoop();
}

void MainGame::initSystems()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);



	// Set window var and position its x and y center to center of screen
	_window = SDL_CreateWindow("Graphics Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	// If window fails, log fatal error
	if (_window == nullptr)
	{
		fatalError("SDL Window couldn't be opened!");
	}

	SDL_GLContext glContex = SDL_GL_CreateContext(_window);

	// Fatal error if context fails
	if (glContex == nullptr)
	{
		fatalError("SDL_GL context could not be created!");
	}


	// Fatal error if flew fails
	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		fatalError("Could not initialize glew!");
	}
	
	// Create 2 buffers
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Set background buffer
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

	initShaders();
}

void MainGame::initShaders()
{
	// Compile shader files
	_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
	// Add the attributes declared in the shader
	_colorProgram.addAttribute("vertexPosition");
	_colorProgram.addAttribute("vertexColor");
	// Link the shaders
	_colorProgram.linkShaders();
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event evnt;

	// What even do we need to process?
	while (SDL_PollEvent(&evnt))
	{
		switch (evnt.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << evnt.motion.x << " " << evnt.motion.y << std::endl;
			break;
		}			
	}
}

void MainGame::drawGame()
{
	// Tells OpenGL what depth to clear to
	glClearDepth(1.0f);
	// Clears screen (buffer)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_colorProgram.Use();

	_sprite.draw();

	_colorProgram.unUse();

	SDL_GL_SwapWindow(_window);
}

