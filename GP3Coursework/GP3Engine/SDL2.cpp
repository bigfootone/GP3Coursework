#include "Common.h"
#include "SDL2.h"

int initSDL2()
{
	//init everything - SDL, if it is nonZero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init " << SDL_GetError() << std::endl;

		return -1;
	}

}

void initSDL2Image()
{
	//init SDL image
	int imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	int returnInitFlags = IMG_Init(imageInitFlags);
	if (((returnInitFlags)& (imageInitFlags)) != imageInitFlags)
	{
		cout << "Error SDL_Image Init " << IMG_GetError() << endl;
	}

}

void initSDL2TTF()
{
	//init SDL font
	if (TTF_Init() == -1)
	{
		cout << "ERROR TTF_Init: " << TTF_GetError();
	}

}