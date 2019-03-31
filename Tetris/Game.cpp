#include "Game.h"

#include <SDL.h>
#include <SDL_image.h>

#include "utilities.h"


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


	auto imageInitResult = IMG_Init(IMG_INIT_PNG);

	if (!(imageInitResult & IMG_INIT_PNG) )
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

	_spriteSheet = ::LoadImage("C:/development/Tetris/img/spritesheet.png", _backBuffer);

	if (_spriteSheet == 0)
	{
		return false;
	}
	return true;
}

void Game::Run()
{
	const int tiles[20][25] = {
		{ 8, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
		{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 }
	};
		

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

		SDL_Rect srcRect;
		
		srcRect.w = 32;
		srcRect.h = 32;
		srcRect.x = 0;
		srcRect.y = 0;

		SDL_Rect destRect;
		destRect.w = 32;
		destRect.h = 32;

		for (int i = 0; i < _screenHeight / 32; i++)
		{
			destRect.y = i * 32;
			for (int j = 0; j < _screenWidth / 32; j++)
			{
				destRect.x = j * 32;


				int tileIndex = tiles[i][j];

				srcRect.x = (tileIndex % 5) * 32;
				srcRect.y = (tileIndex / 5) * 32;

				

				SDL_BlitSurface(_spriteSheet,&srcRect, _backBuffer, &destRect);
			}
		}

		SDL_UpdateWindowSurface(_window);
	}
}

void Game::CleanUp()
{

	SDL_FreeSurface(_spriteSheet);
	SDL_DestroyWindow(_window);
	SDL_Quit();
}


Game::~Game()
{
}
