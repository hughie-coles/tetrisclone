#include "Game.h"

#include <SDL.h>


Game::Game()
{
}

bool Game::Init()
{
	auto initResult = SDL_Init(SDL_INIT_VIDEO);

	if (initResult < 0)
	{
		return false;
	}

	_window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN);

	if (_window == 0)
	{
		return 1;
	}

	_backBuffer = SDL_GetWindowSurface(_window);

	if (_backBuffer == 0)
	{
		return false;
	}

	return true;
}

void Game::Run()
{

	bool isRunning = true;

	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			//User requests quit
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}

		SDL_FillRect(_backBuffer, NULL, SDL_MapRGB(_backBuffer->format, 0xFF, 0x00, 0x00));
		SDL_UpdateWindowSurface(_window);
	}
}

void Game::CleanUp()
{
	SDL_DestroyWindow(_window);
	SDL_Quit();
}


Game::~Game()
{
}
