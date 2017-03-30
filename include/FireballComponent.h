#pragma once

#include "Common.h"
#include "Components\BaseComponent.h"
#include "GameObject.h"

class FireballComponent : public Component
{
public:
	FireballComponent(GameObject *tempOwner);
	~FireballComponent();

	void update(mat4 MVPMat) override;

	bool collision(GameObject* target);
};
