#include "GameInputComponent.h"



GameInputComponent::GameInputComponent(GameObject *tempOwner)
{
	type = "input component";
	owner = tempOwner;
	keyboardListeners.push_back(this);
	playerCon = (GamePlayerController*)owner->getInput();
	missileCount = 0;
}


GameInputComponent::~GameInputComponent()
{
}

void GameInputComponent::onKeyDown(SDL_Keycode key)
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

void GameInputComponent::onkeyUp(SDL_Keycode key)
{
}

void GameInputComponent::mouseMove(SDL_MouseMotionEvent motion)
{
	owner->getInput()->mouseMovment(vec2(motion.x, motion.y));
	SDL_WarpMouseInWindow(getWin(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}

void GameInputComponent::mouseDown(SDL_MouseButtonEvent button)
{
	if (button.button == SDL_BUTTON_LEFT)
	{
		playerCon->FirePrimWeapon();

		string TempName = "missile" + to_string(missileCount);
		owner->addChild(new GameObject(TempName, owner, missileObject, missileTexture, missileShader));	//creating object
		owner->getChild(TempName)->addComponent(new Renderer(owner->getChild(TempName)));	//adding render comp

		missileCount++;
		btVector3 FirePosition = btVector3(owner->getWorldPos().x, owner->getWorldPos().y, owner->getWorldPos().z);
		//cout << "position " << owner->getWorldPos().x << " " << owner->getWorldPos().y << " " << owner->getWorldPos().z << endl;
		btRigidBody* missile1 = bulPhys->CreatePhysBox(FirePosition, 1, missileShapeID);
		//TODO set the firce direction forward

		btVector3 fireForce = btVector3(playerCon->getlookAtPoint().x * 1000, playerCon->getlookAtPoint().y * 1000, playerCon->getlookAtPoint().z * 1000);
		missile1->applyForce(fireForce, FirePosition);
		
		owner->getChild(TempName)->addComponent(new physicsComponent(owner->getChild(TempName), missile1)); //adding physics comp
		owner->getChild(TempName)->setPosition(vec3(0,0,0));	//changing postiion
		owner->getChild(TempName)->setRotation(vec3(0, 0, 0));	//change rotaion
		owner->getChild(TempName)->setScale(vec3(1, 1, 1));	//change scele
		owner->getChild(TempName)->setForceRender(true);
	}
}

void GameInputComponent::mouseUp(SDL_MouseButtonEvent button)
{
}
