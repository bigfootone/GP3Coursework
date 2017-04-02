#include "FireballComponent.h"

FireballComponent::FireballComponent(GameObject *tempOwner)
{
	type = "fireball component";
	owner = tempOwner;
}

FireballComponent::~FireballComponent()
{

}

void FireballComponent::update(mat4 MVPMat)
{

}

bool FireballComponent::collision(GameObject* target)
{
	cout << "collided" << endl;

	//owner->setDestroy(true);
	//target->setDestroy(true);

	return true;
}