#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include "Common.h"
#include "PlayerController.h"

class InputManager
{
private:
	SDL_Event event;
public:
	void KeyBoardPress(PlayerController *player);
};


#endif