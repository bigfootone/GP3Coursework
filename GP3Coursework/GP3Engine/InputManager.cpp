#include "Common.h"
#include "InputManager.h"


void InputManager::KeyBoardPress(PlayerController *player)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			player->moveForward();
			break;
		case SDLK_s:
			player->moveBackward();
			break;
		case SDLK_a:
			player->strafeLeft();
			break;
		case SDLK_d:
			player->strafeRight();
			break;
		default:
			break;
		}
	}	
}

