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
	if (activeLight)
	{
		activeLight->m_lightPosition = vec4(owner->getWorldPos(), 1);
	}

	if (SDL_GetTicks() - lifespan  > 1000)
	{
		owner->setDestroy(true);
	}
}

bool FireballComponent::collision(GameObject* target)
{

	if (target->getName() == "targetIce")
	{
		cout << target->getName() << endl;
		owner->setDestroy(true);
		target->setDestroy(true);
	}
	return true;
}

