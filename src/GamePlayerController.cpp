#include "GamePlayerController.h"

GamePlayerController::GamePlayerController()
{
}

void GamePlayerController::FirePrimWeapon()
{
	cout << "fire wep" << endl;
}

void GamePlayerController::moveForward()
{
	position += forward * speed;
}

void GamePlayerController::moveBackward()
{
	position -= forward * speed;
}

void GamePlayerController::strafeRight()
{
	position += right * speed;
}

void GamePlayerController::strafeLeft()
{
	position -= right * speed;
}
