#include "IceballComponent.h"

IceballComponent::IceballComponent(GameObject *tempOwner)
{
	type = "Iceball Component";
	owner = tempOwner;
	lifespan = SDL_GetTicks();
}

IceballComponent::~IceballComponent()
{

}

void IceballComponent::update(mat4 MVPMat)
{
	if (SDL_GetTicks() - lifespan  > 1000)
	{
		owner->setDestroy(true);
	}
}

bool IceballComponent::collision(GameObject* target)
{


	if(target->getName().find("targetFire") != string::npos)
	{
		cout << target->getName() << endl;
		owner->setDestroy(true);
		target->setDestroy(true);
	}

	return true;

}