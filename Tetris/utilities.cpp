


#include "utilities.h"



SDL_Surface* LoadImage(std::string imagePath, SDL_Surface *windowSurface)
{
	SDL_Surface *optimizedSurface = 0;
	SDL_Surface *loadedImage = IMG_Load(imagePath.c_str());

	if (loadedImage == 0)
	{
		return 0;
	}

	optimizedSurface = SDL_ConvertSurface(loadedImage, windowSurface->format, 0);

	SDL_FreeSurface(loadedImage);

	return optimizedSurface;
}