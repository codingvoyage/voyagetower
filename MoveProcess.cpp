#include "MoveProcess.h"
#include "Services.h"
#include "PhysicsComponent.h"

// Default constructor
MoveProcess::MoveProcess(int targetObjectID, float targetDistance, float vx, float vy) :
	targetObjectID(targetObjectID),
	targetDistance(targetDistance),
	vx(vx),
	vy(vy)
{
	distanceElapsed = 0.0f;
	// Register targetObjectID as an object being used.
}

// error - remember delegating constructor cannot have another mem-initializer
// including superclass constructors, apparently. 
MoveProcess::MoveProcess(int callbkCoroutine, int targetObjectID, 
	float targetDistance, float vx, float vy) :
	LuaCallbackProcess(callbkCoroutine),
	targetObjectID(targetObjectID),
	targetDistance(targetDistance),
	vx(vx),
	vy(vy)
{
	distanceElapsed = 0.0f;
}

// Default destructor
MoveProcess::~MoveProcess()
{
	cout << "Destroyed MoveProcess for " << targetObjectID << endl;
	// Unregister targetObjectID
}

void MoveProcess::update(float dt)
{
	//cout << " Distance elapsed: " << distanceElapsed << ". Target distance: " << targetDistance << endl;
	if (distanceElapsed < targetDistance)
	{
		// Come to think of it I once read an article saying we
		// were doing our integration wrong. Please look that up?
		float dx = vx * dt;
		float dy = vy * dt;

		// Easy optimization when I have the time - avoid the sqrt!
		distanceElapsed += sqrt(dx*dx + dy*dy);
		
		PhysicsComponent* p = (PhysicsComponent*)Services::componentManager()
			->gameObjGetComponentOfType(targetObjectID, ComponentType::PHYSICS);
		
		// Why does PhysicsComponent not have a "add to" method?
		// Implement later
		p->newx(p->getx() + dx);
		p->newy(p->gety() + dy);
	}
	else
	{
		// distanceElapsed >= targetDistance, so finalize
		deactivate();
	}

}

void MoveProcess::start()
{

}

void MoveProcess::onFinish()
{
	// CallBack
	cout << "Callback time!" << endl;
	LuaCallbackProcess::onFinish();
}
