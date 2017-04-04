#include "FireballComponent.h"

Lighting* FireballComponent::activeLight = nullptr;	

FireballComponent::FireballComponent(GameObject *tempOwner)
{
	type = "fireball component";
	owner = tempOwner;
	lifespan = SDL_GetTicks();
}

FireballComponent::~FireballComponent()
{

}

void FireballComponent::update(mat4 MVPMat)
{
	//update light source location
	if (activeLight)
	{
		activeLight->m_lightPosition = vec4(owner->getWorldPos(), 1);
	}

	//destroy fireball after 1 second
	if (SDL_GetTicks() - lifespan  > 1000)
	{
		owner->setDestroy(true);
	}
}

bool FireballComponent::collision(GameObject* target)
{
	//once a collision occurs, destroy both the fireball and the target
	if (target->getName().find("targetIce") != string::npos)
	{
		cout << target->getName() << endl;
		owner->setDestroy(true);
		target->setDestroy(true);
	}
	return true;
}

