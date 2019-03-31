#pragma once


#include <string> 
struct SDL_Window;
struct SDL_Surface;

class Game
{
public:
	Game();

	bool Init();
	void Run();
	void CleanUp();
	~Game();

private:
	SDL_Window *_window;
	SDL_Surface *_backBuffer;
	SDL_Surface *_spriteSheet;

	const int _screenWidth = 800;
	const int _screenHeight = 640;
	const std::string windowTitle = "Tetris";
};

