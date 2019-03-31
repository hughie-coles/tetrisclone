#pragma once


#include <string> 
class SDL_Window;
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


	const int _screenWidth = 800;
	const int _screenHeight = 600;
	const std::string windowTitle = "Tetris";






};

