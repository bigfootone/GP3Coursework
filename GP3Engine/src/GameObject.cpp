#include "GameObject.h"
#include "Components\InputComponent.h"

Scene* GameObject::curScene = NULL;

GameObject::GameObject()
{
}

GameObject::GameObject(string tempName)
{
	world = true;
	name = tempName;
	parent = NULL;
	model = NULL;
	texture = NULL;
	shader = NULL;
	input = NULL;
	childrenList.clear();
	componentsList.clear();
	active = true;
}

GameObject::GameObject(string tempName, GameObject *tempParent, Object *tempModel, Texture *tempTexture, Shader *tempShader)
{
	world = false;
	name = tempName;
	parent = tempParent;
	model = tempModel;
	texture = tempTexture;
	shader = tempShader;
	input = NULL;
	childrenList.clear();
	componentsList.clear();
	active = true;
}

GameObject::GameObject(string tempName, GameObject *tempParent, PlayerController *tempInput)
{
	world = false;
	name = tempName;
	parent = tempParent;
	model = NULL;
	texture = NULL;
	shader = NULL;
	input = tempInput;
	childrenList.clear();
	componentsList.clear();
	active = true;
}

GameObject::GameObject(string tempName, GameObject *tempParent)
{
	world = false;
	name = tempName;
	parent = tempParent;
	model = NULL;
	texture = NULL;
	shader = NULL;
	input = NULL;
	childrenList.clear();
	componentsList.clear();
	active = true;
}

GameObject::~GameObject()
{
}

void GameObject::update(mat4 VPMat)
{
	modelMatrix = translate(mat4(1.0f), localPos);
	modelMatrix = rotate(modelMatrix, radians(rotation.x), vec3(1, 0, 0));
	modelMatrix = rotate(modelMatrix, radians(rotation.y), vec3(0, 1, 0));
	modelMatrix = rotate(modelMatrix, radians(rotation.z), vec3(0, 0, 1));
	modelMatrix = scale(modelMatrix, size);
	MVP = VPMat * modelMatrix;

	if (active)
	{
		for (auto i = componentsList.begin(); i != componentsList.end(); i++)
		{
			i->second->update(MVP);
		}
		for (auto i = childrenList.begin(); i != childrenList.end(); i++)
		{
			i->second->update(VPMat);
		}
	}
}

void GameObject::render(Fustrum* fustrum)
{
	if (active)
	{
		if (model != NULL)
		{
			//see if the model is inside the fustrum then render
			positionToFrustrum pos = fustrum->isInFrustrum(model->getBoundingBox()->radius, localPos);
			if (forceRender == true || pos == INSIDE_FRUSTRUM || pos == INTERSECT_FRUSTRUM)
			{
				for (auto i = componentsList.begin(); i != componentsList.end(); i++)
				{
					i->second->render();
				}
			}
		}
		for (auto i = childrenList.begin(); i != childrenList.end(); i++)
		{
			i->second->render(fustrum);
		}
	}
}

void GameObject::addComponent(Component *newComp)
{
	cout << "adding render Comp to " << name << endl;
	componentsList.insert(pair<string, Component*>(newComp->getType(), newComp));
}

void GameObject::addChild(GameObject *tempChild)
{
	childrenList.insert(pair<string, GameObject*>(tempChild->getName(), tempChild));
}

void GameObject::changePosition(vec3 tempPos)
{
	localPos += tempPos;
}

GameObject *GameObject::findChild(string com)
{
	for each (auto child in childrenList)
	{
		if (child.first == com)
		{
			return child.second;
		}
		else
		{
			return child.second->findChild(com);
		}
	}
	return NULL;
}

void GameObject::printChildern()
{
	for (auto i = childrenList.begin(); i != childrenList.end(); i++)
	{
		cout << "object: " << i->second->getName() << " components ";
		i->second->printComponents();
		i->second->printChildern();
	}
}

void GameObject::printComponents()
{
	cout << " " << componentsList.size() << " ";
	for (auto i = componentsList.begin(); i != componentsList.end(); i++)
	{
		cout << i->second->getType() << " ";
	}
	cout << endl;
}

vec3 GameObject::getWorldPos()
{
	vec3 TempPos = localPos;
	if (world == false)
	{
		TempPos += parent->getWorldPos();
	}
	return TempPos;

}