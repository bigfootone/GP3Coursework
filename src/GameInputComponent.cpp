#include "GameInputComponent.h"



GameInputComponent::GameInputComponent(GameObject *tempOwner)
{
	type = "input component";
	owner = tempOwner;
	keyboardListeners.push_back(this);
	playerCon = (GamePlayerController*)owner->getInput();
	fireballCount = 0;
	isMoveForward = false;
	isMoveBack = false;
	isMoveLeft = false;
	isMoveRight = false;
}

GameInputComponent::~GameInputComponent()
{

}

void GameInputComponent::update(mat4 MVPMat)
{
	if (isMoveForward == true)
	{
		owner->getInput()->moveForward();
	}
	if (isMoveBack  == true)
	{
		owner->getInput()->moveBackward();
	}
	if (isMoveLeft == true)
	{
		owner->getInput()->strafeLeft();
	}
	if (isMoveRight == true)
	{
		owner->getInput()->strafeRight();
	}
	owner->setPosition(owner->getInput()->getWorldPoint());
}


void GameInputComponent::onKeyDown(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_w:
		isMoveForward = true;
		isMoveBack = false;
		break;
	case SDLK_s:
		isMoveBack = true;
		isMoveForward = false;
		break;
	case SDLK_a:
		isMoveLeft = true;
		break;
	case SDLK_d:
		isMoveRight = true;
		break;
	}
}

void GameInputComponent::onkeyUp(SDL_Keycode key)
{
	switch (key)
	{
	case SDLK_w:
		isMoveForward = false;
		break;
	case SDLK_s:
		isMoveBack = false;
		break;
	case SDLK_a:
		isMoveLeft = false;
		break;
	case SDLK_d:
		isMoveRight = false;
		break;
	}
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

		GameObject* thisFireball;
		string TempName = "fireball" + to_string(fireballCount);

		thisFireball = new GameObject( TempName, owner, fireballObject, fireballTexture, fireballShader);	//creating object
		owner->addChild(thisFireball);
		fireballCount++;

		btVector3 FirePosition = btVector3(owner->getWorldPos().x, owner->getWorldPos().y, owner->getWorldPos().z);
		cout << "position " << owner->getWorldPos().x << " " << owner->getWorldPos().y << " " << owner->getWorldPos().z << endl;
		btRigidBody* missile1 = bulPhys->CreatePhysBox(FirePosition, 1, fireballShapeID);
		//TODO set the firce direction forward

		btVector3 fireForce = btVector3(playerCon->getlookAtPoint().x * 10000, playerCon->getlookAtPoint().y * 10000, playerCon->getlookAtPoint().z * 10000);
		missile1->applyForce(fireForce, FirePosition);
		
		thisFireball->addComponent(new Renderer(owner->getChild(TempName)));
		thisFireball->addComponent(new FireballComponent(owner->getChild(TempName)));
		thisFireball->addComponent(new physicsComponent(owner->getChild(TempName), missile1)); //adding physics comp
		thisFireball->setPosition(vec3(0, 0, 0));	//changing postiion
		thisFireball->setRotation(vec3(0, 0, 0));	//change rotaion
		thisFireball->setScale(vec3(0.2, 0.2, 0.2));	//change scale
		thisFireball->setForceRender(true);
	}
}

void GameInputComponent::mouseUp(SDL_MouseButtonEvent button)
{
}
