



#include <SDL.h>

#include <string>

#include "Game.h"

int main(int argc, char** argv)
{

	Game game;

	if (!game.Init())
	{
		return -1;
	}

	game.Run();

	game.CleanUp();

	return 0;
}
