#pragma once
#include "Components\InputComponent.h"
#include "GamePlayerController.h"
#include "physicsComponent.h"
#include "BulletPhys.h"
#include "FireballComponent.h"

class GameInputComponent :public InputComponent
{
public:
	GameInputComponent(GameObject *tempOwner);
	~GameInputComponent();

	void update(mat4 MVPMat) override;
	void onKeyDown(SDL_Keycode key) override;
	void onkeyUp(SDL_Keycode key) override;
	void mouseMove(SDL_MouseMotionEvent motion) override;
	void mouseDown(SDL_MouseButtonEvent button) override;
	void mouseUp(SDL_MouseButtonEvent button) override;

	void assignBulPhys(BulletPhys* tempBul) { bulPhys = tempBul; };
	void assignMissile(Object* tempObject, Shader* tempShader, Texture* tempTexture, int shapeID, BulletPhys* TempPhys) { fireballObject = tempObject, fireballShader = tempShader, fireballTexture = tempTexture, fireballShapeID = shapeID, bulPhys = TempPhys; };

private:
	GamePlayerController *playerCon;
	bool isMoveForward;
	bool isMoveBack;
	bool isMoveLeft;
	bool isMoveRight;

	//fireball 
	Object* fireballObject;
	Shader* fireballShader;
	Texture* fireballTexture;
	int fireballShapeID;

	BulletPhys* bulPhys;

	//fireball count 
	int fireballCount;
};

