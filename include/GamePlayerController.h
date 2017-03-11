#pragma once
#include "PlayerController.h"

class GamePlayerController: public PlayerController
{
public:
	GamePlayerController();
	~GamePlayerController();

	void moveForward() override;
	void moveBackward() override;
	void strafeRight() override;
	void strafeLeft() override;

	void FirePrimWeapon();
};

