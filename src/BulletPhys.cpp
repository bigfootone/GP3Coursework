#include "BulletPhys.h"



BulletPhys::BulletPhys()
{
	//from https://github.com/bulletphysics/bullet3/blob/master/examples/HelloWorld/HelloWorld.cpp   bullet hello world tutorial

	//collision configuration contains default setup for memory, collision setup.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	//use the default collision dispatcher.
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	//btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	//the default constraint solver.
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	//set gravity
	dynamicsWorld->setGravity(btVector3(0, 0, 0));
}


BulletPhys::~BulletPhys()
{
	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;
}

void BulletPhys::CreateGroundPlane()
{
	//taken from bullet hello world example

	//the ground is a cube of side 100 at position y = -56.
	//the sphere will hit it at y = -6, with center at -5

	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

	collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, -56, 0));

	btScalar mass(0.);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(body);
}

btRigidBody* BulletPhys::CreatePhysBox(btVector3 StartPos, float TempMass, int ID)
{
	//create a dynamic rigidbody

	btCollisionShape* colShape = collisionShapes[ID];
	//btCollisionShape* colShape = new btSphereShape(btScalar(1.));
	collisionShapes.push_back(colShape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar	mass(TempMass);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		colShape->calculateLocalInertia(mass, localInertia);

	startTransform.setOrigin(StartPos);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	dynamicsWorld->addRigidBody(body);

	return body;
}

int BulletPhys::CreateBoxShape(btVector3 size)
{
	btCollisionShape* colShape = new btBoxShape(size);
	collisionShapes.push_back(colShape);
	return (collisionShapes.size() - 1);
}

int BulletPhys::CreateSphereShape(double size)
{
	btCollisionShape* colShape = new btSphereShape(btScalar(size));
	collisionShapes.push_back(colShape);
	return (collisionShapes.size() - 1);
}


void BulletPhys::updatePhysics()
{
	dynamicsWorld->stepSimulation(1.f / 60.f, 10);

	dynamicsWorld->debugDrawWorld();

	//print positions of all objects
	for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);

		}
		else
		{
			trans = obj->getWorldTransform();
		}
	}

	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();

		GameObject* objectA = (GameObject*)obA->getUserPointer();
		GameObject* objectB = (GameObject*)obB->getUserPointer();

		int numContacts = contactManifold->getNumContacts();
		if (objectA && objectB)
		{
			// check to see if either object is a fireball or iceball and if it is then perform collision work
			FireballComponent* tempFireballComponent = (FireballComponent*)objectA->getComponents("fireball component");
			IceballComponent* tempIceballComponent = (IceballComponent*)objectA->getComponents("Iceball Component");
			if (tempFireballComponent)
			{
				tempFireballComponent->collision(objectB);
			}
			else if (tempIceballComponent)
			{
				tempIceballComponent->collision(objectB);
			}
			else
			{
				tempFireballComponent = (FireballComponent*)objectB->getComponents("fireball component");
				tempIceballComponent = (IceballComponent*)objectB->getComponents("Iceball Component");
				if(tempFireballComponent)
				{
					tempFireballComponent->collision(objectA);
				}
				else if (tempIceballComponent)
				{
					tempIceballComponent->collision(objectA);
				}
			}
		}

	}
}

btRigidBody* BulletPhys::getRidgidBody(int ID)
{
	btCollisionObject* tempShape = dynamicsWorld->getCollisionObjectArray()[ID];
	return btRigidBody::upcast(tempShape);
}

btVector3 BulletPhys::getPosition(btRigidBody* body)
{
	btTransform trans;
	body->getMotionState()->getWorldTransform(trans);
	return trans.getOrigin();
}

void BulletPhys::removePhysics(btRigidBody* tempbody)
{
	dynamicsWorld->removeRigidBody(tempbody);
}
	