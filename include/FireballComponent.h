#pragma once

#include "Common.h"
#include "Components\BaseComponent.h"
#include "GameObject.h"
#include "Material.h"
#include "Lighting.h"

class FireballComponent : public Component
{
public:
	FireballComponent(GameObject *tempOwner);
	~FireballComponent();

	void update(mat4 MVPMat) override;

	bool collision(GameObject* target);
	void setMaterial(Material newMat) { mat = newMat; };
	Material getMaterial() { return mat; }
	Lighting getLight() { return light; }
	void setLighting(Lighting newLight) { light = newLight; activeLight = &light; };
	
	static Lighting* getActiveLight() { return activeLight; }

private:
	//material
	Material mat;
	Lighting light;

	static Lighting *activeLight;

	float lifespan;
	float lastTime;
};
