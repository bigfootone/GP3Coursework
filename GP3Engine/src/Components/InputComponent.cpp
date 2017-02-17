#include "Components\InputComponent.h"

InputComponent::InputComponent(){}

InputComponent::InputComponent(GameObject *tempOwner)
{
	type = "input component";
	owner = tempOwner;
	keyboardListeners.push_back(this);
}
void InputComponent::onKeyDown(SDL_Keycode key)
	{
		switch (key)
		{
		case SDLK_w:
			owner->getInput()->moveForward();
			break;
		case SDLK_s:
			owner->getInput()->moveBackward();
			break;
		case SDLK_a:
			owner->getInput()->strafeLeft();
			break;
		case SDLK_d:
			owner->getInput()->strafeRight();
			break;
		}
		owner->setPosition(owner->getInput()->getWorldPoint());
	}

void InputComponent::onkeyUp(SDL_Keycode key)
{
}

void InputComponent::mouseMove(SDL_MouseMotionEvent motion)
{
	owner->getInput()->mouseMovment(vec2(motion.x, motion.y));
	SDL_WarpMouseInWindow(getWin(), SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}
