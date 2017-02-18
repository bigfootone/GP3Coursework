#pragma once

#include "btBulletDynamicsCommon.h"

class BulletPhys
{
public:
	BulletPhys();
	~BulletPhys();
	void CreateGroundPlane();
	void CreatePhysBox();
	void CreatePhysSphere();
	void updatePhysics();
	btRigidBody* getRidgidBody(int ID);
	btVector3 getPosition(btRigidBody* body);


private:
	//init objects
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;

	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;
};

