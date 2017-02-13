#ifndef _INPUTCOMPONENT_H
#define _INPUTCOMPONENT_H

#include "Common.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "KeyboardListener.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "Window.h"

class InputComponent : public IkeyboardListener, public Component{

public:
	InputComponent();
	InputComponent(GameObject *tempOwner);
	virtual ~InputComponent(){}

	void onKeyDown(SDL_Keycode key) override;
	void onkeyUp(SDL_Keycode key) override;
	void mouseMove(SDL_MouseMotionEvent motion) override;

private:
	vec2 curMousePos;
};

#endif