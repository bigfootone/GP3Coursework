#include "physicsComponent.h"



physicsComponent::physicsComponent()
{
	type = "physics component";
}


physicsComponent::physicsComponent(GameObject *tempOwner, btRigidBody* tempRidgidBody)
{
	type = "physics component";
	owner = tempOwner;
	ridgidBody = tempRidgidBody;
	ridgidBody->setUserPointer(owner);
}

physicsComponent::~physicsComponent()
{

}

void physicsComponent::update(mat4 MVPMat)
{
	MVP = MVPMat;

	btTransform trans;
	ridgidBody->getMotionState()->getWorldTransform(trans);

	btVector3 BTpos = trans.getOrigin();
	vec3 vecPos = vec3(BTpos.x(), BTpos.y(), BTpos.z());
	
	btVector3 BTrot = trans.getRotation().getAxis();
	vec3 vecRot = vec3(BTrot.x(), BTrot.y(), BTrot.z());
	
	owner->setPosition(vecPos);
	//owner->setRotation(vecRot);
}

string physicsComponent::getType()
{
	return string();
}
