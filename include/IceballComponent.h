#pragma once

#include "Common.h"
#include "Components\BaseComponent.h"
#include "GameObject.h"

class IceballComponent : public Component
{
public:
	IceballComponent(GameObject *tempOwner);
	~IceballComponent();

	void update(mat4 MVPMat) override;

	bool collision(GameObject* target);
};
#pragma once
