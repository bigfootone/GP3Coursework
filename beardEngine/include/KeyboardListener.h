#ifndef _KEYBOARDLISTENER_H
#define _KEYBOARDLISTENER_H

#include "Common.h"

class IkeyboardListener
{
public:
	virtual ~IkeyboardListener(){}
	virtual void onKeyDown(SDL_Keycode key) = 0;
	virtual void onkeyUp(SDL_Keycode key) = 0;
	virtual void mouseMove(SDL_MouseMotionEvent motion) = 0;


private:

};

#endif
