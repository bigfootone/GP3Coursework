#include "IceballComponent.h"

IceballComponent::IceballComponent(GameObject *tempOwner)
{
	type = "Iceball Component";
	owner = tempOwner;
}

IceballComponent::~IceballComponent()
{

}

void IceballComponent::update(mat4 MVPMat)
{

}

bool IceballComponent::collision(GameObject* target)
{

	if (target->getName() == "targetIce")
	{
		cout << target->getName() << endl;
	}
	//owner->setDestroy(true);
	//target->setDestroy(true);

	return true;

}