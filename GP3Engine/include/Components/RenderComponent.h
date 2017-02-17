#ifndef _RENDERCOMPONENT_H
#define _RENDERCOMPONENT_H

#include "Common.h"
#include "BaseComponent.h"
#include "Object.h"

class Renderer:public Component
{
public:
	Renderer();
	Renderer(GameObject *tempOwner);
	~Renderer();

	void init() override;
	void update(mat4 MVPMat) override;
	void render() override;
	string getType() override;
private:

};

#endif