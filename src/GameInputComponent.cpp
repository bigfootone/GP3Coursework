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
	currentSpell = 1;
	controllerCameraX = false;
	controllerCameraY = false;
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

	if (controllerCameraX == true || controllerCameraY == true)
	{

		//SDL_WarpMouseInWindow(getWin(), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		//owner->getInput()->mouseMovment(vec2(motion.x, motion.y));

		controllerLookX = (SCREEN_WIDTH / 2);
		controllerLookY = (SCREEN_HEIGHT / 2);

		controllerLookX = controllerLookX + currentXValue;
		controllerLookY = controllerLookY + currentYValue;

		owner->getInput()->mouseMovment(vec2(controllerLookX, controllerLookY));

	}
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
	case SDLK_1:
		currentSpell = 1;
		cout << currentSpell << endl;
		break;
	case SDLK_2:
		currentSpell = 2;
		cout << currentSpell << endl;
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
		if (currentSpell == 1)
		{
			shootFireball();
		}
		if (currentSpell == 2)
		{
			shootIceball();
		}
	}
}

void GameInputComponent::mouseUp(SDL_MouseButtonEvent button)
{
}

void GameInputComponent::controllerButtonDown(SDL_ControllerButtonEvent button)
{
	if (button.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
	{
		shootFireball();
	}
	else if (button.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
	{
		shootIceball();
	}
}

void GameInputComponent::controllerStickInput(SDL_ControllerAxisEvent motion)
{
	switch (motion.axis)
	{
	case SDL_CONTROLLER_AXIS_LEFTX:
		if (motion.value > 15000)
		{
			isMoveRight = true;
		}
		else if (motion.value < -15000)
		{
			isMoveLeft = true;
		}
		else
		{
			isMoveRight = false;
			isMoveLeft = false;
		}
		break;
	case SDL_CONTROLLER_AXIS_LEFTY:
		if (motion.value < -15000)
		{
			isMoveForward = true;
		}
		else if (motion.value > 15000)
		{
			isMoveBack = true;
		}
		else
		{
			isMoveForward = false;
			isMoveBack = false;
		}
		break;
	case SDL_CONTROLLER_AXIS_RIGHTX:
		if (motion.value > 15000)
		{
			controllerCameraX = true;
			currentXValue = motion.value / 3767;
		}
		else if (motion.value < -15000)
		{
			controllerCameraX = true;
			currentXValue = motion.value / 3767;
		}
		else 
		{
			controllerCameraX = false;
			currentXValue = 0;
		}
		break;
	case SDL_CONTROLLER_AXIS_RIGHTY:
		if (motion.value > 15000)
		{
			controllerCameraY = true;
			currentYValue = motion.value / 3767;
		}
		else if (motion.value < -15000)
		{
			controllerCameraY = true;
			currentYValue = motion.value / 3767;
		}
		else
		{
			controllerCameraY = false;
			currentYValue = 0;
		}
	}
}

void GameInputComponent::shootFireball()
{
	playerCon->FirePrimWeapon();

	GameObject* thisFireball;
	string TempName = "fireball" + to_string(fireballCount);

	thisFireball = new GameObject(TempName, owner, fireballObject, fireballTexture, fireballShader);	//creating object
	owner->addChild(thisFireball);
	fireballCount++;

	btVector3 FirePosition = btVector3(owner->getWorldPos().x, owner->getWorldPos().y, owner->getWorldPos().z);
	cout << "position " << owner->getWorldPos().x << " " << owner->getWorldPos().y << " " << owner->getWorldPos().z << endl;
	btRigidBody* missile1 = bulPhys->CreatePhysBox(FirePosition, 1, fireballShapeID);

	btVector3 fireForce = btVector3(playerCon->getlookAtPoint().x * 500, playerCon->getlookAtPoint().y * 500, playerCon->getlookAtPoint().z * 500);
	missile1->applyForce(fireForce, FirePosition);

	thisFireball->addComponent(new Renderer(owner->getChild(TempName)));
	FireballComponent* fireball = new FireballComponent(owner->getChild(TempName));
	Material spellMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 5.0f);
	fireball->setMaterial(spellMaterial);
	Lighting light(lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, 20, 1), glm::vec3(0.0, 0.0, 1.0), 0.0f, 10.0f, 1.0f, 0.0f, 0.0f);
	fireball->setLighting(light);
	thisFireball->addComponent(fireball);
	thisFireball->addComponent(new physicsComponent(owner->getChild(TempName), missile1, bulPhys)); //adding physics comp
	thisFireball->setPosition(vec3(0, 0, 0));	//changing postiion
	thisFireball->setRotation(vec3(0, 0, 0));	//change rotaion
	thisFireball->setScale(vec3(0.2, 0.2, 0.2));	//change scale
	thisFireball->setForceRender(true);

	//audio
	Audio* fireAudio;
	fireAudio = new Audio();
	fireAudio->createBuffer("/fireball.wav");
	fireAudio->playAudio();
}

void GameInputComponent::shootIceball()
{
	playerCon->FirePrimWeapon();

	GameObject* thisIceball;
	string TempName = "iceball" + to_string(fireballCount);

	thisIceball = new GameObject(TempName, owner, iceballObject, iceballTexture, iceballShader);	//creating object
	owner->addChild(thisIceball);
	fireballCount++;

	btVector3 FirePosition = btVector3(owner->getWorldPos().x, owner->getWorldPos().y, owner->getWorldPos().z);
	cout << "position " << owner->getWorldPos().x << " " << owner->getWorldPos().y << " " << owner->getWorldPos().z << endl;
	btRigidBody* missile1 = bulPhys->CreatePhysBox(FirePosition, 1, fireballShapeID);

	btVector3 fireForce = btVector3(playerCon->getlookAtPoint().x * 10000, playerCon->getlookAtPoint().y * 10000, playerCon->getlookAtPoint().z * 10000);
	missile1->applyForce(fireForce, FirePosition);

	thisIceball->addComponent(new Renderer(owner->getChild(TempName)));
	thisIceball->addComponent(new IceballComponent(owner->getChild(TempName)));
	thisIceball->addComponent(new physicsComponent(owner->getChild(TempName), missile1, bulPhys)); //adding physics comp
	thisIceball->setPosition(vec3(0, 0, 0));	//changing postiion
	thisIceball->setRotation(vec3(0, 0, 0));	//change rotaion
	thisIceball->setScale(vec3(0.2, 0.2, 0.2));	//change scale
	thisIceball->setForceRender(true);

	//music
	Audio* fireAudio;
	fireAudio = new Audio();
	fireAudio->createBuffer("/iceball.wav");
	fireAudio->playAudio();
}
